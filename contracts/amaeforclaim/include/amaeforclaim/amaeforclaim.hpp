#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>
#include <string>
#include <wasm_db.hpp>
#include "amaeforclaim/amax.token.hpp"
#include "amaeforclaim/amaeforclaim.db.hpp"

namespace amax {

using std::string;
using namespace eosio;
using namespace wasm::db;

/**
 * The `amaeforclaim` is Cross-chain (X -> AMAX -> Y) contract
 * 
 */

#define TRANSFER(bank, to, quantity, memo) \
    {	token::transfer_action act{ bank, { {_self, active_perm} } };\
			act.send( _self, to, quantity , memo );}
static string to_hex(const checksum256 &hashed) {
    // Construct variables
    string result;
    const char *hex_chars = "0123456789abcdef";
    const auto bytes = hashed.extract_as_byte_array();
    // Iterate hash and build result
    for (uint32_t i = 0; i < bytes.size(); ++i) {
        (result += hex_chars[(bytes.at(i) >> 4)]) += hex_chars[(bytes.at(i) & 0x0f)];
    }
    // Return string
    return result;
}

static const char* charmap = "0123456789";

std::string uint128ToString(const uint128_t& value)
{
    std::string result;
    result.reserve( 40 ); // max. 40 digits possible ( uint64_t has 20) 
    uint128_t helper = value;

    do {
        result += charmap[ helper % 10 ];
        helper /= 10;
    } while ( helper );
    std::reverse( result.begin(), result.end() );
    return result;
}

class [[eosio::contract("amaeforclaim")]] amaeforclaim : public contract {
private:
   dbc                 _db;
   global_singleton    _global;
   global_t            _gstate;

public:
   using contract::contract;

   amaeforclaim(eosio::name receiver, eosio::name code, datastream<const char*> ds):
        _db(_self), contract(receiver, code, ds), 
        _global(_self, _self.value){
            
        if (_global.exists()) {
            _gstate = _global.get();

        } else { // first init
            _gstate = global_t{};
            _gstate.admin = _self;
        }
    }

    ~amaeforclaim() { 
        _global.set( _gstate, get_self() );
    }
   
    
    ACTION claim( const name& to, const string& str_hash, const asset& quantity );

    ACTION init( const name& admin) {
        _check_admin( );
    
        _gstate.admin           = admin;
    }
    private:
     void _check_admin(){
         CHECKC( has_auth(_self) || has_auth(_gstate.admin), err::NO_AUTH, "no auth for operate" )
      }

};
} //namespace apollo
