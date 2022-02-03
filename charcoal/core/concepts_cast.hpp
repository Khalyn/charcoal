#pragma once

#ifndef __cpp_lib_concepts
#define __cpp_lib_concepts // Concepts doesn't work in CLion without it, see https://www.jetbrains.com/help/clion/c-20-concepts.html#configure-concepts
#endif
#include <concepts>

// Defining a concept where the user can use the static_cast without any restriction.
template<typename Wanted, typename From> concept AllowUnsafeStaticCast =
requires ( From value )
{
	{ static_cast<Wanted>( value ) } -> std::same_as<Wanted>;
};

// Defining a concept that can only allow the static_cast operation when it's safe to use it.
template<typename Wanted, typename From> concept AllowStaticCast =
	AllowUnsafeStaticCast<Wanted, From> and
    ( sizeof( Wanted ) > sizeof( From ) or ( sizeof( Wanted ) == sizeof( From ) and std::is_unsigned_v<Wanted> ) );

