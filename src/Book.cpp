#include "../include/Book.h"
#include <sstream>
#include <algorithm>
#include <cctype>

Book::Book() : year(0), rating(0.0) {}

Book::Book(const std::string& id, const std::string& title, const std::string& author,
           const std::string& description, const std::string& coverImage, int year,
           const std::vector<std::string>& genres, const std::string& isbn, double rating)
    : id(id), title(title), author(author), description(description),
      coverImage(coverImage), year(year), genres(genres), isbn(isbn), rating(rating) {}

bool Book::matchesFilter(const std::string& authorFilter, int yearFilter,
                        const std::string& genreFilter, const std::string& promptFilter) const {
    // Author filter
    if (!authorFilter.empty()) {
        std::string authorLower = author;
        std::string filterLower = authorFilter;
        std::transform(authorLower.begin(), authorLower.end(), authorLower.begin(), ::tolower);
        std::transform(filterLower.begin(), filterLower.end(), filterLower.begin(), ::tolower);
        if (authorLower.find(filterLower) == std::string::npos) {
            return false;
        }
    }
    
    // Year filter
    if (yearFilter > 0 && year < yearFilter) {
        return false;
    }
    
    // Genre filter
    if (!genreFilter.empty()) {
        bool genreMatch = false;
        std::string filterLower = genreFilter;
        std::transform(filterLower.begin(), filterLower.end(), filterLower.begin(), ::tolower);
        for (const auto& genre : genres) {
            std::string genreLower = genre;
            std::transform(genreLower.begin(), genreLower.end(), genreLower.begin(), ::tolower);
            if (genreLower == filterLower) {
                genreMatch = true;
                break;
            }
        }
        if (!genreMatch) {
            return false;
        }
    }
    
    // Prompt filter (search in title and description)
    if (!promptFilter.empty()) {
        std::string titleLower = title;
        std::string descLower = description;
        std::string promptLower = promptFilter;
        std::transform(titleLower.begin(), titleLower.end(), titleLower.begin(), ::tolower);
        std::transform(descLower.begin(), descLower.end(), descLower.begin(), ::tolower);
        std::transform(promptLower.begin(), promptLower.end(), promptLower.begin(), ::tolower);
        
        if (titleLower.find(promptLower) == std::string::npos &&
            descLower.find(promptLower) == std::string::npos) {
            return false;
        }
    }
    
    return true;
}

std::string Book::toJson() const {
    std::ostringstream oss;
    oss << "{\"id\":\"" << id << "\",\"title\":\"" << title << "\",\"author\":\"" << author
        << "\",\"description\":\"" << description << "\",\"coverImage\":\"" << coverImage
        << "\",\"year\":" << year << ",\"genres\":[";
    for (size_t i = 0; i < genres.size(); ++i) {
        if (i > 0) oss << ",";
        oss << "\"" << genres[i] << "\"";
    }
    oss << "],\"isbn\":\"" << isbn << "\",\"rating\":" << rating << "}";
    return oss.str();
}

Book Book::fromJson(const std::string& json) {
    // Simple JSON parsing (for production, use a proper JSON library)
    Book book;
    // This is a simplified parser - in production, use nlohmann/json or similar
    size_t pos = json.find("\"id\":\"");
    if (pos != std::string::npos) {
        pos += 6;
        size_t end = json.find("\"", pos);
        if (end != std::string::npos) book.id = json.substr(pos, end - pos);
    }
    // Similar parsing for other fields...
    return book;
}

