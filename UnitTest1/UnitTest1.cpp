#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab12.13(3)/lab12.13(3).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestAddNote)
        {
            OpenHashTable hashTable;
            Note note = { "Doe", "John", "123456789", {1, 4, 1990} };

            hashTable.addNote(note);
            vector<Note> result;
            bool found = hashTable.findNoteByLastName("Doe", result);

            Assert::IsTrue(found, L"Failed to find note after adding.");
            Assert::AreEqual(1, static_cast<int>(result.size()), L"Incorrect number of notes found.");
            Assert::AreEqual(note.lastName, result[0].lastName, L"Last name does not match.");
            Assert::AreEqual(note.firstName, result[0].firstName, L"First name does not match.");
            Assert::AreEqual(note.phoneNumber, result[0].phoneNumber, L"Phone number does not match.");
            Assert::AreEqual(note.birthDate[0], result[0].birthDate[0], L"Birth date day does not match.");
            Assert::AreEqual(note.birthDate[1], result[0].birthDate[1], L"Birth date month does not match.");
            Assert::AreEqual(note.birthDate[2], result[0].birthDate[2], L"Birth date year does not match.");
        }

        TEST_METHOD(TestDeleteNote)
        {
            OpenHashTable hashTable;
            Note note1 = { "Doe", "John", "123456789", {1, 4, 1990} };
            Note note2 = { "Smith", "Alice", "987654321", {15, 8, 1985} };

            hashTable.addNote(note1);
            hashTable.addNote(note2);

            hashTable.deleteNote("Doe", "John");
            vector<Note> result;
            bool foundDoe = hashTable.findNoteByLastName("Doe", result);

            Assert::IsFalse(foundDoe, L"Note not deleted properly.");
            Assert::AreEqual(0, static_cast<int>(result.size()), L"Incorrect number of notes found after deletion.");
        }

        TEST_METHOD(TestFindNoteByLastName)
        {
            OpenHashTable hashTable;
            Note note1 = { "Doe", "John", "123456789", {1, 4, 1990} };
            Note note2 = { "Doe", "Jane", "987654321", {15, 8, 1985} };

            hashTable.addNote(note1);
            hashTable.addNote(note2);

            vector<Note> result;
            bool found = hashTable.findNoteByLastName("Doe", result);

            Assert::IsTrue(found, L"Failed to find notes by last name.");
            Assert::AreEqual(2, static_cast<int>(result.size()), L"Incorrect number of notes found.");
        }
	};
}