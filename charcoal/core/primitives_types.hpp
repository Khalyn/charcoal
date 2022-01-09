#pragma once

#include <cstdint>

#include "boolean.hpp"

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
			explicit constexpr PrimitiveType( T const &value )
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

			// TODO methods
			inline constexpr auto as_inner() const noexcept -> inner_type
			{
				return m_data;
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
		//TODO Better compile-time tests
	} // inline namespace tests_ct

} // namespace charcoal
