#pragma once

#include <cstdint>
#include <string>

namespace ve {

	/**
	 * Provides storage and resolution utilities for standard HTML entity escape sequences.
	 **/
	class Html {
	public :
		// == Enumerations.
		/**
		 * Sentinel values for invalid HTML entity lookups.
		 * 
		 * \note These values are used when a name does not map to a recognized entity or an index is out of range.
		 **/
		enum class InvalidCode : uint32_t {
			Invalid = 0xFFFFFFFF
		};


		// == Types.
		/**
		 * Represents a single HTML entity mapping.
		 **/
		struct EntityEntry {
			/** The exact literal name of the entity (e.g., “aacute”). **/
			const char*						name;
			/** The character length of the name. **/
			uint32_t						length;
			/** The number of valid Unicode code points this entity maps to (usually 1 or 2). **/
			uint32_t						totalVals;
			/** The array of Unicode code points. **/
			uint32_t						val[2];
		};


		// == Functions.
		/**
		 * Gets the total number of entity names in the table.
		 *
		 * \return				Returns the number of entries available via getName()/getNameLength().
		 **/
		static size_t						totalNames();

		/**
		 * Gets an entity name by index as a narrow string.
		 * Must be called within a try/catch block.
		 *
		 * \param ret			Receives the entity name.
		 * \param index			Index of the name to retrieve.
		 * \return				Returns a reference to the populated string.
		 *
		 * \note				If index is out of range, the returned string is cleared to an empty value.
		 **/
		static std::string&					getName(std::string& ret, size_t index);

		/**
		 * Gets an entity name by index as a wide string.
		 * Must be called within a try/catch block.
		 *
		 * \param ret			Receives the entity name.
		 * \param index			Index of the name to retrieve.
		 * \return				Returns a reference to the populated wide string.
		 *
		 * \note				If index is out of range, the returned string is cleared to an empty value.
		 **/
		static std::wstring&				getName(std::wstring& ret, size_t index);

		/**
		 * Gets the length of an entity name by index.
		 *
		 * \param index			Index of the name to query.
		 * \return				Returns the length of the name at the specified index, or 0 if index is out of range.
		 **/
		static size_t						getNameLength(size_t index) {
			if (index < totalNames()) {
				return entities[index].length;
			}
			else {
				return 0;
			}
		}

		/**
		 * Gets the HTML entity value given its name (case-sensitive).
		 *
		 * \param name			Pointer to the entity name (not including surrounding '&' and ';').
		 * \param len			Length of the name string in bytes.
		 * \return				Returns the Unicode code point(s) associated with the name packed into a 64-bit unsigned integer, or InvalidCode::Invalid if not found.
		 *
		 * \note				Lookup is case-sensitive (for example, "lt" and "LT" are treated as distinct names if both exist in the table).
		 *						If the entity resolves to two code points, the second code point is shifted into the upper 32 bits.
		 **/
		static uint64_t						getCode(const char* name, size_t len);

	private :
		/** The internal static array containing all HTML entity mappings. **/
		static const EntityEntry			entities[];
	};

}