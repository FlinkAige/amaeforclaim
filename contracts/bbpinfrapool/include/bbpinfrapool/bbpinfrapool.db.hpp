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

static constexpr symbol AMAX_SYMBOL              = SYMBOL("AMAX", 8);
static constexpr name  AMAX_BANK                = "amax.token"_n;

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

#define TBL struct [[eosio::table, eosio::contract("bbpinfrapool")]]


struct [[eosio::table("global"), eosio::contract("bbpinfrapool")]] global_t {
    name     admin         = "amaxapplybbp"_n;                 
    asset    total_claimed = asset(0, AMAX_SYMBOL); 
    name     last_idx; 
    uint32_t bbp_count     = 0;

    EOSLIB_SERIALIZE( global_t, (admin)(total_claimed)(last_idx)(bbp_count) )
};
typedef eosio::singleton< "global"_n, global_t > global_singleton;


TBL bbp_t {
    name            account;
    name            rewarder;
    time_point_sec  created_at;
    time_point_sec  updated_at;

    bbp_t() {};

    uint64_t    primary_key()const { return account.value; }

    typedef eosio::multi_index<"bbps"_n, bbp_t> idx_t;

    EOSLIB_SERIALIZE( bbp_t, (account)(rewarder)(created_at)(updated_at) )
};

} // amax
