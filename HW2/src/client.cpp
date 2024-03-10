#include "client.h"

Client::Client(std::string id, const Server& server)
    : server(&server), id(id), public_key({}), private_key({})
{
    crypto::generate_key(public_key, private_key);
}

std::string Client::get_id() const
{
    return id;
}

std::string Client::get_publickey() const
{
    return public_key;
}

double Client::get_wallet() const
{
    return server->get_wallet(id);
}

std::string Client::sign(std::string txt) const
{
    return crypto::signMessage(private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value)
{
    std::stringstream ss;
    ss << value;
    std::string value_string;
    ss >> value_string;
    std::string trx = id + "-" + receiver + "-" + value_string; 
    std::string signature = sign(trx);
    return server->add_pending_trx(trx, signature);
}

size_t Client::generate_nonce()
{
    return rand();
}