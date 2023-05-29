#include "DocumentManager.h"

void DocumentManager::addDocument(std::string name, int id, int license_limit) {
    if (documents.find(id) != documents.end()) {
        // Document with the same ID already exists
        return;
    }

    Document doc;
    doc.name = std::move(name);
    doc.id = id;
    doc.license_limit = license_limit;
    doc.copies_borrowed = 0;

    documents.insert(std::make_pair(id, std::move(doc)));
};

void DocumentManager::addPatron(int patronID) {
    patrons.insert(patronID);
};

int DocumentManager::search(std::string name) {
    for (const auto& pair : documents) {
        if (pair.second.name == name) {
            return pair.first;
        }
    }

    return 0;  // Document not found
};


bool DocumentManager::borrowDocument(int docid, int patronID) {
    auto it = documents.find(docid);
    if (it == documents.end()) {
        // Document with the given ID does not exist
        return false;
    }

    Document& doc = it->second;
    if (patrons.find(patronID) == patrons.end()) {
        // Patron with the given ID does not exist
        return false;
    }

    if (doc.copies_borrowed >= doc.license_limit) {
        // All copies of the document are already borrowed
        return false;
    }

    doc.copies_borrowed++;
    doc.borrowed_by.insert(patronID);
    return true;
};

void DocumentManager::returnDocument(int docid, int patronID) {
    auto it = documents.find(docid);
    if (it == documents.end()) {
        // Document with the given ID does not exist
        return;
    }

    Document& doc = it->second;
    doc.copies_borrowed--;
    doc.borrowed_by.erase(patronID);
};