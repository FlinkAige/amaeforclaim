#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>
#include <string>
#include <wasm_db.hpp>
#include "bbpinfrapool/amax.token.hpp"
#include "bbpinfrapool/bbpinfrapool.db.hpp"

namespace amax {

using std::string;
using namespace eosio;
using namespace wasm::db;

/**
 * The `bbpinfrapool` is Cross-chain (X -> AMAX -> Y) contract
 * 
 */

#define TRANSFER(bank, to, quantity, memo) \
    {	token::transfer_action act{ bank, { {_self, active_perm} } };\
			act.send( _self, to, quantity , memo );}

class [[eosio::contract("bbpinfrapool")]] bbpinfrapool : public contract {
private:
   dbc                 _db;
   global_singleton    _global;
   global_t            _gstate;
  bbp_t::idx_t         _bbp_t;
public:
   using contract::contract;

   bbpinfrapool(eosio::name receiver, eosio::name code, datastream<const char*> ds):
        _db(_self), contract(receiver, code, ds), 
        _bbp_t(get_self(), get_self().value),
        _global(_self, _self.value){
            
        if (_global.exists()) {
            _gstate = _global.get();

        } else { // first init
            _gstate = global_t{};
            _gstate.admin = _self;
        }
    }

    ~bbpinfrapool() { 
        _global.set( _gstate, get_self() );
    }
   
    
    ACTION claim(const uint32_t& count);

    ACTION init( const name& admin) {
        _check_admin( );
        _gstate.admin  = admin;
    }
    ACTION addbbp( const std::vector<name>& bbps,const name& rewarder) {
        _check_admin( );

        for (auto& bbp : bbps) {
            auto bbp_itr = _bbp_t.find( bbp.value );
            CHECKC(bbp_itr ==  _bbp_t.end(), err::RECORD_EXISTING, "bbp already exists" );
            _bbp_t.emplace( _self, [&]( auto& row ) {
                row.account     = bbp;
                row.rewarder    = rewarder;
                row.created_at  = current_time_point();
                row.updated_at  = current_time_point();
            });
            _gstate.bbp_count++;
            
        }
    }
    ACTION delbbp( const std::vector<name>& bbps) {
        _check_admin( );

        for (auto& bbp : bbps) {
            auto bbp_itr = _bbp_t.find( bbp.value );
            CHECKC(bbp_itr !=  _bbp_t.end(), err::RECORD_NOT_FOUND, "bbp not found" );
            _bbp_t.erase( bbp_itr );
            _gstate.bbp_count--;
        }
    }

    private:
     void _check_admin(){
         CHECKC( has_auth(_self) || has_auth(_gstate.admin), err::NO_AUTH, "no auth for operate" )
      }

};
} //namespace apollo
