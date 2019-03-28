// Copyright (c) 2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_PEGTL_CONTRIB_CHANGE_ACTION_AND_STATES_HPP
#define TAO_PEGTL_CONTRIB_CHANGE_ACTION_AND_STATES_HPP

#include <tuple>

#include "../internal/integer_sequence.hpp"

#include "../apply_mode.hpp"
#include "../config.hpp"
#include "../match.hpp"
#include "../rewind_mode.hpp"

namespace tao
{
   namespace TAO_PEGTL_NAMESPACE
   {
      template< template< typename... > class NewAction, typename... NewStates >
      struct change_action_and_states
      {
         template< typename Rule,
                   apply_mode A,
                   rewind_mode M,
                   template< typename... >
                   class Action,
                   template< typename... >
                   class Control,
                   std::size_t... Ns,
                   typename Input,
                   typename... States >
         static bool match( TAO_PEGTL_NAMESPACE::internal::index_sequence< Ns... >, Input& in, States&&... st )
         {
            auto t = std::tie( st... );
            if( TAO_PEGTL_NAMESPACE::match< Rule, A, M, NewAction, Control >( in, std::get< Ns >( t )... ) ) {
               if( A == apply_mode::action ) {
                  Action< Rule >::success( static_cast< const Input& >( in ), st... );
               }
               return true;
            }
            return false;
         }

         template< typename Rule,
                   apply_mode A,
                   rewind_mode M,
                   template< typename... >
                   class Action,
                   template< typename... >
                   class Control,
                   typename Input,
                   typename... States >
         static bool match( Input& in, States&&... st )
         {
            return match< Rule, A, M, Action, Control >( TAO_PEGTL_NAMESPACE::internal::index_sequence_for< NewStates... >(), in, NewStates()..., st... );
         }
      };

   }  // namespace TAO_PEGTL_NAMESPACE

}  // namespace tao

#endif
