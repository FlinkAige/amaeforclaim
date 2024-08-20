 #pragma once

#include <eosio/asset.hpp>
#include <eosio/privileged.hpp>
#include <eosio/singleton.hpp>
#include <eosio/system.hpp>
#include <eosio/time.hpp>
#include <utils.hpp>

#include <deque>
#include <optional>
#include <string>
#include <map>
#include <set>
#include <type_traits>

namespace amax {

using namespace std;
using namespace eosio;

#define SYMBOL(sym_code, precision) symbol(symbol_code(sym_code), precision)

static constexpr eosio::name active_perm{"active"_n};

static constexpr uint64_t percent_boost     = 10000;
static constexpr uint64_t max_memo_size     = 1024;
static constexpr uint64_t max_addr_len      = 128;

static constexpr symbol AMAE_SYMBOL              = SYMBOL("AMAE", 8);
static constexpr name  AMAE_BANK                = "amae.token"_n;

#define hash(str) sha256(const_cast<char*>(str.c_str()), str.size())

enum class err: uint8_t {
    NONE                = 0,
    RECORD_NOT_FOUND    = 1,
    RECORD_EXISTING     = 2,
    ADDRESS_ILLEGAL     = 3,
    SYMBOL_MISMATCH     = 4,
    ADDRESS_MISMATCH    = 5,
    NOT_COMMON_XIN      = 6,
    STATUS_INCORRECT    = 7,
    PARAM_INCORRECT     = 8,
    NO_AUTH             = 9,

};

#define TBL struct [[eosio::table, eosio::contract("amaeforclaim")]]


struct [[eosio::table("global2"), eosio::contract("amaeforclaim")]] global_t {
    name admin;                 
    asset total_claimed = asset(0, AMAE_SYMBOL);  

    EOSLIB_SERIALIZE( global_t, (admin)(total_claimed) )
};
typedef eosio::singleton< "global2"_n, global_t > global_singleton;


TBL order_t {
    uint64_t        id;         //PK
    name            account;
    string          str_hash;       //mobile_hash
    asset           quantity;   //for deposit_quantity
    time_point_sec  created_at;
    time_point_sec  updated_at;

    order_t() {};

    uint64_t    primary_key()const { return id; }

    uint64_t    by_account() const { return account.value; }
    checksum256   by_hash() const { return hash(str_hash); }

    typedef eosio::multi_index<"orders"_n, order_t,
        indexed_by<"accoutidx"_n, const_mem_fun<order_t, uint64_t, &order_t::by_account> >,
        indexed_by<"hashidx"_n, const_mem_fun<order_t, checksum256, &order_t::by_hash> >
    > idx_t;

    EOSLIB_SERIALIZE( order_t, (id)(account)(str_hash)(quantity)(created_at)(updated_at) )
};

} // amax
