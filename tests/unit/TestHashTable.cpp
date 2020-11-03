/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 02-Nov-2020
 */

//--------------------------------------------------------------------------------------------------
#include "catch2/catch.hpp"
#include "HashTable.hpp"

//--------------------------------------------------------------------------------------------------

namespace tests
{

SCENARIO( "HashTable testing", "[hash_table]" ) {
    GIVEN( "HashTable HashTableChaining" ) {
        hash::HashTableChaining<size_t, std::string> hashTable(31);
        hashTable.put(1, "world");

        WHEN( "Item was added to the hash table" ) {
            THEN( "It was saved correctly and can be retrieved" ) {
                REQUIRE( "world" == hashTable.get(1) );
            }
        }
        WHEN( "Item with the same key was added to the hash table" ) {
            hashTable.put(1, "table");
            THEN( "The value of the item is replaced by the new" ) {
                REQUIRE( "table" == hashTable.get(1) );
            }
        }
        WHEN( "Item with the same hash code was added to the hash table" ) {
            hashTable.put(32, "cat");
            THEN( "All items with the same hash code are present" ) {
                REQUIRE( "world" == hashTable.get(1) );
                REQUIRE( "cat" == hashTable.get(32) );
            }
        }
        WHEN( "Retrieve vale of unexisting item" ) {
            THEN( "Value-initialized value returns" ) {
                REQUIRE( "" == hashTable.get(2) );
            }
        }
        WHEN( "Delete the item" ) {
            hashTable.del(1);
            THEN( "Item was deleted" ) {
                REQUIRE( "" == hashTable.get(1) );
            }
        }
        WHEN( "Delete the item with the same hash code" ) {
            hashTable.put(32, "cat");
            hashTable.del(1);
            THEN( "Proper item was deleted" ) {
                REQUIRE( "" == hashTable.get(1) );
                REQUIRE( "cat" == hashTable.get(32) );
            }
        }
    }
}

} // namespace tests
