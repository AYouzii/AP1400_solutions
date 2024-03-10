#include "server.h"

void show_wallets(const Server& server)
{
	std::cout << std::string(20, '*') << std::endl;
	for(const auto& client: server.clients)
		std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
	std::cout << std::string(20, '*') << std::endl;
}

std::vector<std::string> pending_trxs;

std::shared_ptr<Client> Server::add_client(std::string id)
{
    bool id_already_exists = false;
    std::shared_ptr<Client> new_client;

    for (std::map<std::shared_ptr<Client>, double>::const_iterator it = clients.cbegin(); it != clients.cend(); ++it) {
        if (it->first->get_id() == id) {
            std::stringstream ss;
            ss << std::setw(4) << std::setfill('0') << rand() % 10000;
            std::string postfix;
            ss >> postfix;
            std::string new_id = id + postfix;
            new_client = std::make_shared<Client>(new_id, *this);
            clients[new_client] = 5;
            id_already_exists = true;
            break;
        }
    }

    if (! id_already_exists) {
        new_client = std::make_shared<Client>(id, *this);
        clients[new_client] = 5;
    }

    return new_client;
}

std::shared_ptr<Client> Server::get_client(std::string id) const
{
    for (std::map<std::shared_ptr<Client>, double>::const_iterator cit = clients.cbegin(); cit != clients.cend(); ++cit) {
        if (cit->first->get_id() == id) {
            return cit->first;
        }
    }

    return nullptr;
}

double Server::get_wallet(std::string id) const
{
    for (auto cit = clients.cbegin(); cit != clients.cend(); ++cit) {
        if (cit->first->get_id() == id) {
            return cit->second;
        }
    }
    return -1;
}

bool Server::parse_trx(const std::string& trx, std::string& sender, std::string& receiver, double& value)
{
    if (trx.empty()) {
        throw std::runtime_error("Got empty trx!");
    }
    bool sender_parsed = false, receiver_parsed = false;
    unsigned first_dash_position = 0, second_dash_position = 0;
    for (unsigned i = 0; i < trx.size(); ++i) {
        if (trx[i] == '-') {
            if (! sender_parsed) {
                if (i == 1) {
                    throw std::runtime_error("missing sender");
                }
                else {
                    std::string trx_sender(trx.cbegin(), trx.cbegin() + i);
                    sender = trx_sender;
                }
                sender_parsed = true;
                first_dash_position = i;
                continue;
            }

            if (! receiver_parsed) {
                if(i - first_dash_position < 2) {
                    throw std::runtime_error("missing receiver");
                } 
                else {
                    std::string trx_receiver(trx.cbegin() + first_dash_position + 1, trx.cbegin() + i);
                    receiver = trx_receiver;
                }
                receiver_parsed = true;
                second_dash_position = i;
                if (i + 1 == trx.size()) {
                    throw std::runtime_error("missing value");
                }
                std::string trx_value(trx.cbegin() + second_dash_position + 1, trx.cend());
                value = std::stod(trx_value);
                break;
           }
        }
    }
    if (sender_parsed && receiver_parsed) {
        return true;
    }
    else {
        throw std::runtime_error("non-standard trx");
    }
}

bool Server::add_pending_trx(std::string trx, std::string signature) const
{
    std::string sender, receiver;
    double value;
    Server::parse_trx(trx, sender, receiver, value);

    if (! get_client(receiver)) {
        return false;
    }
    double balance = get_wallet(sender);
    if (balance < value) {
        return false;
    }
    else {
        std::shared_ptr<Client> send_client = get_client(sender);
        if (crypto::verifySignature(send_client->get_publickey(), trx, signature)) {
            pending_trxs.push_back(trx);
            return true;
        }
        else {
            return false;
        }
    }
}

size_t Server::mine(void)
{
    std::string transaction_string;
    // Step 1: concatenate all the trx strings.
    for (const std::string& trx : pending_trxs) {
        transaction_string += trx;
    }
    // Step 2: for each client, generate a nonce and the corresponding hash string.
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        // generate nonce
        size_t nonce = it->first->generate_nonce();
        // concatenate nonce to the end of the mempool
        std::string nonce_string = transaction_string + std::to_string(nonce);
        // generate hash string
        std::string hash_string = crypto::sha256(nonce_string);
        // check if the generated sha256 has 3 zeros in a row
        if (hash_string.substr(0, 10).find("000") != hash_string.npos) {
            // print out the miner
            std::cout << it->first->get_id() << std::endl;
            for (const std::string& trx : pending_trxs) {
                // complete the transactions
                std::string sender, receiver;
                double value;
                Server::parse_trx(trx, sender, receiver, value);
                for (auto iit = clients.begin(); iit != clients.end(); ++iit) {
                    if (iit->first->get_id() == sender) {
                        iit->second -= value;
                    }
                    if (iit->first->get_id() == receiver) {
                        iit->second += value;
                    }
                }
            }
            // award the client with correct nonce
            it->second += 6.25;
            // clear all pending transactions
            std::vector<std::string>().swap(pending_trxs);
            // return nonce and mine done
            return nonce;
        }
    }
    return -1;
}