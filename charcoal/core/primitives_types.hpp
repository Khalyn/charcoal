#pragma once

#include <cstdint>

#include "charcoal/core/boolean.hpp"
#include "charcoal/core/concepts_cast.hpp"

namespace charcoal
{
	namespace impl
	{
		template<typename T>
		class PrimitiveType
		{
		public:
			using type = PrimitiveType;
			using inner_type = T;

			static inline constexpr inner_type BYTES = sizeof( inner_type );

			// constructors
			constexpr explicit PrimitiveType( T const &value )
				: m_data( value )
			{};

			PrimitiveType( type const &value ) = default;

			// operators overload
			explicit constexpr operator inner_type() const { return m_data; }

			[[nodiscard]] constexpr auto operator ==( inner_type const &rhs ) const -> boolean
			{
				return boolean( m_data == rhs );
			}

			[[nodiscard]] constexpr auto operator ==( type const &rhs ) const -> boolean
			{
				return m_data == rhs.m_data;
			}


			[[nodiscard]] constexpr auto operator !=( inner_type const &rhs ) const -> boolean
			{
				return boolean( m_data != rhs );
			}

			[[nodiscard]] constexpr auto operator !=( type const &rhs ) const -> boolean
			{
				return m_data != rhs.m_data;
			}

			// methods
			[[nodiscard]] inline constexpr auto as_inner() const noexcept -> inner_type
			{
				return m_data;
			}


			template<AllowStaticCast<inner_type> Wanted>
			[[nodiscard]] inline constexpr auto as() const noexcept -> Wanted
			{
				return static_cast<Wanted>( m_data );
			}

			template<AllowUnsafeStaticCast<inner_type> Wanted>
			[[nodiscard]] inline constexpr auto as_unsafe() const noexcept -> Wanted
			{
#pragma warning( disable: 4244 ) // Disable the warning : conversion from 'X' to 'Y', possible loss of data
				return static_cast<Wanted>( m_data );
#pragma warning( default: 4244 )
			}

		private:
			inner_type m_data;
		};
	} // namespace impl


	// TODO Add least and fast unsigned/signed types.
	using u8 = impl::PrimitiveType<uint8_t>;
	using u16 = impl::PrimitiveType<uint16_t>;
	using u32 = impl::PrimitiveType<uint32_t>;
	using u64 = impl::PrimitiveType<uint64_t>;

	using i8 = impl::PrimitiveType<int8_t>;
	using i16 = impl::PrimitiveType<int16_t>;
	using i32 = impl::PrimitiveType<int32_t>;
	using i64 = impl::PrimitiveType<int64_t>;

	using f32 = impl::PrimitiveType<float>;
	using f64 = impl::PrimitiveType<double>;


	inline namespace tests_ct
	{
		static_assert( u8( 6 ) == 6 );
		static_assert( u8::BYTES == sizeof( uint8_t) );

		consteval bool compile_time_casts()
		{
			u8 const a( 128 );
			u16 const fromA = a.as<u16>();
			u8 const fromFromA = fromA.as_unsafe<u8>(); // as doesn't compile here
			i8 const b = fromFromA.as_unsafe<i8>(); // as doesn't compile here
			return true;
		}

		static_assert( compile_time_casts() );
		//TODO Better compile-time tests
	} // inline namespace tests_ct

} // namespace charcoal
