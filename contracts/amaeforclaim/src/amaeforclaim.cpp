#include <amaeforclaim/amaeforclaim.hpp>

#include <eosio/transaction.hpp>
#include<utils.hpp>
#include<math.hpp>
#include<string>


namespace amax {

ACTION amaeforclaim::claim( const name& to, const string& str_hash, const asset& quantity,const uint32_t& needpay)
{
   _check_admin();

   CHECKC( quantity.symbol == AMAE_SYMBOL, err::SYMBOL_MISMATCH, "symbol mismatch" );

   auto orders = order_t::idx_t(_self, _self.value);
   auto itr = orders.get_index<"hashidx"_n>();
   CHECKC( itr.find( hash(str_hash) ) == itr.end(), err::RECORD_EXISTING, "hash already exists" );

   auto account_itr = orders.get_index<"accoutidx"_n>();
   CHECKC( account_itr.find( to.value ) == account_itr.end(), err::RECORD_EXISTING, "to account already exists" );

   auto now                   = current_time_point();

   orders.emplace( _self, [&]( auto& row ) {
      row.id 					   = orders.available_primary_key();;
      row.account             = to;
      row.str_hash            = str_hash;
      row.quantity            = quantity;
      row.status              = needpay;
      row.created_at          = now;
      row.updated_at          = now;
   });

   if( needpay == 1 ) {
      TRANSFER( AMAE_BANK, to, quantity, "" );
      _gstate.total_claimed += quantity;
   }

}




} //namespace amax

