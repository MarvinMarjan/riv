#pragma once

#include <vector>

#include <scanner/token.h>



class Scanner
{
public:
	Scanner(const std::string& source);


	std::vector<Token> scan();


private:
	std::vector<Token> tokens_;

	std::string source_;
	size_t line_, begin_, end_;

	size_t& current_ = end_;


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