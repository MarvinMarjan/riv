#pragma once

#include <vector>

#include <scanner/token.h>



// a Scanner takes a source and scans it into tokens
class Scanner
{
public:
	Scanner(const std::string& source);


	std::vector<Token> scan();


private:
	// resulting tokens
	std::vector<Token> tokens_;

	// source string
	std::string source_;

	// locality utils
	size_t line_, begin_, end_;


	size_t& current_ = end_;


	// scans the token
	void scan_token();


	bool at_end()		const	noexcept;
	char advance()				noexcept;
	char peek()			const	noexcept;
	char peek_next()	const	noexcept;

	bool match(const char next) noexcept;


	void add_token(const TokenType type) noexcept {
		tokens_.push_back(Token(type, current_substring(), line_, begin_, end_));
	}


	std::string current_substring() const noexcept {
		return source_.substr(begin_, end_ - begin_);
	}
};