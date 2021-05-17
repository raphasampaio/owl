#pragma once

#ifndef OWL_STRING_H
#define OWL_STRING_H

#include <codecvt>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace std {
	inline std::string to_string(std::string s) {
		return s;
	}
}

namespace owl::string {
	inline std::string trim(std::string s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !std::isspace(ch); }));
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !std::isspace(ch); }).base(), s.end());
		return s;
	}

	inline bool has_ending(std::string const& s, std::string const& ending) {
		if (s.length() >= ending.length()) {
			return (0 == s.compare(s.length() - ending.length(), ending.length(), ending));
		} else {
			return false;
		}
	}

	inline std::vector<std::string> split(const std::string& s, char delimiter = ',') {
		std::vector<std::string> tokens;
		std::string token;

		std::istringstream stream(s);
		while (std::getline(stream, token, delimiter)) { tokens.push_back(trim(token)); }
		return tokens;
	}

	inline std::vector<std::string> split(const std::string& s, const std::string& delimiter = ",") {
		std::vector<std::string> tokens;
		std::size_t start = s.find_first_not_of(delimiter);
		std::size_t end = 0;

		while ((end = s.find_first_of(delimiter, start)) != std::string::npos) {
			tokens.push_back(s.substr(start, end - start));
			start = s.find_first_not_of(delimiter, end);
		}

		if (start != std::string::npos) {
			tokens.push_back(s.substr(start));
		}

		return tokens;
	}

	template <typename T> inline std::string join(std::unordered_set<T> v, std::string delimiter = ",") {
		return std::accumulate(std::begin(v), std::end(v), std::string(), [delimiter](std::string& ss, T p) { return ss.empty() ? std::to_string(p) : ss + delimiter + std::to_string(p); });
	}

	template <typename T> inline std::string join(std::vector<T> v, std::string delimiter = ",") {
		return std::accumulate(std::begin(v), std::end(v), std::string(), [delimiter](std::string& ss, T p) { return ss.empty() ? std::to_string(p) : ss + delimiter + std::to_string(p); });
	}

	template <typename T> inline std::string join_with_preffix(std::vector<T> v, std::string preffix, std::string delimiter = ",") {
		return std::accumulate(std::begin(v), std::end(v), std::string(), [preffix, delimiter](std::string& ss, T p) { return ss.empty() ? (preffix + std::to_string(p)) : ss + delimiter + preffix + std::to_string(p); });
	}

	inline std::string ansi_to_utf8(const std::string& s) {
		std::wstring wstr;
		std::mbstate_t state = {};
		const char* src = s.data();
		size_t len = std::mbsrtowcs(nullptr, &src, 0, &state);
		if (static_cast<size_t>(-1) != len) {
			std::unique_ptr< wchar_t[] > buff(new wchar_t[len + 1]);
			len = std::mbsrtowcs(buff.get(), &src, len, &state);
			if (static_cast<size_t>(-1) != len) {
				wstr.assign(buff.get(), len);
			}
		}

        std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
        return wcv.to_bytes(wstr);
    }
}

#endif