#pragma once

#include <cstdint>
#include <string>
#include <string_view>

#ifdef _WIN32
#include "../OS/OS.h"
#else	// #ifdef _WIN32
#include <iconv.h>
#include <cerrno>
#endif	// #ifdef _WIN32

namespace ve {

	// == Enumerations.
	/**
	 * Represents the policy for handling encoding and decoding errors.
	 **/
	enum class EncodingErrorPolicy : uint8_t {
		Strict,
		Replace
	};

	/**
	 * Represents common code pages for multi-byte and wide character conversions.
	 * Numeric values map directly to Windows Code Page Identifiers where applicable.
	 **/
	enum class CodePage : uint32_t {
#define VE_ENC(id, name, enumName)		enumName = id,
#include "EncodeEnum.inl"
#undef VE_ENC
		/*Utf8 = 65001,
		Utf16 = 1200,
		Windows1252 = 1252,
		Ascii = 20127,
		Iso8859_1 = 28591*/
	};

	/**
	 * Provides cross-platform wrappers for native string encoding and decoding operations.
	 **/
	class Encode {
	public :
		// == Functions.
		/**
		 * Dummy function to map a CodePage enum to an iconv-compatible string descriptor.
		 *
		 * \param codePage		The numeric code page identifier.
		 * \return				Returns a string descriptor (e.g., "SHIFT_JIS").
		 **/
		static const char*				getCodePageString(CodePage codePage);

		/**
		 * Retrieves the CodePage identifier associated with a string descriptor.
		 * Performs a case-insensitive, locale-independent search.
		 *
		 * \param name			The string descriptor to search for (e.g., "SHIFT_JIS").
		 * \param outCodePage	Output parameter to store the resolved CodePage.
		 * \return				Returns true if a matching code page was found, false otherwise.
		 **/
		static bool						getCodePageId(std::string_view name, CodePage& outCodePage);

		/**
		 * Converts a multi-byte string into a wide-character string (16-bit).
		 *
		 * \param codePage		The code page of the input string.
		 * \param input			The input multi-byte string view.
		 * \param errorPolicy	The policy to apply when encountering invalid characters.
		 * \return				Returns the converted 16-bit string.
		 **/
		template <typename StringT>
		static inline StringT			multiByteToWideChar(CodePage codePage, std::string_view input, EncodingErrorPolicy errorPolicy) {
			using CharT = typename StringT::value_type;
			static_assert(sizeof(CharT) == 2, "multiByteToWideChar requires a 16-bit character string type.");

			StringT result;

			if (input.empty()) {
				return result;
			}

#ifdef _WIN32
			int requiredSize = ::MultiByteToWideChar(
				static_cast<UINT>(codePage), 
				0, 
				input.data(), 
				static_cast<int>(input.length()), 
				nullptr, 
				0
			);

			if (requiredSize == 0) {
				DWORD err = ::GetLastError();
				
				if (errorPolicy == EncodingErrorPolicy::Strict) {
					result.clear();
				}
				
				return result;
			}

			result.resize(static_cast<size_t>(requiredSize));
			
			int convertResult = ::MultiByteToWideChar(
				static_cast<UINT>(codePage), 
				0, 
				input.data(), 
				static_cast<int>(input.length()), 
				reinterpret_cast<wchar_t*>(result.data()), 
				requiredSize
			);

			if (convertResult == 0) {
				DWORD err = ::GetLastError();
				
				if (errorPolicy == EncodingErrorPolicy::Strict) {
					result.clear();
				}
			}
#else
			const char* cpStr = getCodePageString(codePage);
			
			iconv_t cd = ::iconv_open("UTF-16LE", cpStr);
			if (cd == reinterpret_cast<iconv_t>(-1)) {
				return result;
			}

			result.resize(input.length());

			char* inbuf = const_cast<char*>(input.data());
			size_t inbytesleft = input.length();
			char* outbuf = reinterpret_cast<char*>(result.data());
			size_t outbytesleft = result.size() * sizeof(CharT);

			while (inbytesleft > 0) {
				size_t res = ::iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
				
				if (res == static_cast<size_t>(-1)) {
					if (errno == EILSEQ || errno == EINVAL) {
						if (errorPolicy == EncodingErrorPolicy::Strict) {
							result.clear();
							break;
						}
						else {
							if (outbytesleft >= sizeof(CharT)) {
								*reinterpret_cast<CharT*>(outbuf) = static_cast<CharT>(0xFFFD);
								outbuf += sizeof(CharT);
								outbytesleft -= sizeof(CharT);
							}
							inbuf++;
							inbytesleft--;
						}
					}
					else {
						break;
					}
				}
			}

			::iconv_close(cd);

			result.resize(result.length() - (outbytesleft / sizeof(CharT)));
#endif

			return result;
		}

		/**
		 * Converts a wide-character string (16-bit) into a multi-byte string.
		 *
		 * \param codePage		The target code page for the output string.
		 * \param input			The input 16-bit wide-character string view.
		 * \param errorPolicy	The policy to apply when encountering invalid characters.
		 * \return				Returns the converted multi-byte string.
		 **/
		template <typename StringT, typename InputCharT>
		static inline StringT			wideCharToMultiByte(CodePage codePage, std::basic_string_view<InputCharT> input, EncodingErrorPolicy errorPolicy) {
			using OutCharT = typename StringT::value_type;
			static_assert(sizeof(InputCharT) == 2, "wideCharToMultiByte requires a 16-bit input character string type.");
			static_assert(sizeof(OutCharT) == 1, "wideCharToMultiByte requires an 8-bit output character string type.");

			StringT result;

			if (input.empty()) {
				return result;
			}

#ifdef _WIN32
			int requiredSize = ::WideCharToMultiByte(
				static_cast<UINT>(codePage), 
				0, 
				reinterpret_cast<LPCWCH>(input.data()), 
				static_cast<int>(input.length()), 
				nullptr, 
				0, 
				nullptr, 
				nullptr
			);

			if (requiredSize == 0) {
				DWORD err = ::GetLastError();
				
				if (errorPolicy == EncodingErrorPolicy::Strict) {
					result.clear();
				}
				
				return result;
			}

			result.resize(static_cast<size_t>(requiredSize));
			
			int convertResult = ::WideCharToMultiByte(
				static_cast<UINT>(codePage), 
				0, 
				reinterpret_cast<LPCWCH>(input.data()), 
				static_cast<int>(input.length()), 
				reinterpret_cast<LPSTR>(result.data()), 
				requiredSize, 
				nullptr, 
				nullptr
			);

			if (convertResult == 0) {
				DWORD err = ::GetLastError();
				
				if (errorPolicy == EncodingErrorPolicy::Strict) {
					result.clear();
				}
			}
#else
			const char* cpStr = getCodePageString(codePage);
			
			iconv_t cd = ::iconv_open(cpStr, "UTF-16LE");
			if (cd == reinterpret_cast<iconv_t>(-1)) {
				return result;
			}

			result.resize(input.length() * 4);

			char* inbuf = const_cast<char*>(reinterpret_cast<const char*>(input.data()));
			size_t inbytesleft = input.length() * sizeof(InputCharT);
			char* outbuf = reinterpret_cast<char*>(result.data());
			size_t outbytesleft = result.size() * sizeof(OutCharT);

			while (inbytesleft > 0) {
				size_t res = ::iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
				
				if (res == static_cast<size_t>(-1)) {
					if (errno == EILSEQ || errno == EINVAL) {
						if (errorPolicy == EncodingErrorPolicy::Strict) {
							result.clear();
							break;
						}
						else {
							if (outbytesleft >= sizeof(OutCharT)) {
								(*reinterpret_cast<OutCharT*>(outbuf)) = static_cast<OutCharT>('?');
								outbuf += sizeof(OutCharT);
								outbytesleft -= sizeof(OutCharT);
							}
							inbuf += sizeof(InputCharT);
							inbytesleft -= sizeof(InputCharT);
						}
					}
					else if (errno == E2BIG) {
						size_t currentOutLen = result.size() - (outbytesleft / sizeof(OutCharT));
						result.resize(result.size() * 2);
						outbuf = reinterpret_cast<char*>(result.data()) + (currentOutLen * sizeof(OutCharT));
						outbytesleft = (result.size() - currentOutLen) * sizeof(OutCharT);
					}
					else {
						break;
					}
				}
			}

			::iconv_close(cd);

			result.resize(result.size() - (outbytesleft / sizeof(OutCharT)));
#endif

			return result;
		}

	protected :
		// == Types.
		/** Relates codepage Windows ID’s to their string names. */
		struct Enum_Mapping {
			CodePage					codePage;
			const char*					name;
		};

		// == Members.
		/** The string-to-ID database. */
		static const Enum_Mapping		enumMapping[];
	};

}	// namespace ve
