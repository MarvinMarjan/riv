#pragma once

#include <string>
#include <vector>



enum class InitMode
{
	REPL,
	SourceFile
};


// gets the initialization mode
InitMode get_init_mode(const int argc, const char** argv) noexcept;


struct Token;

class Statement;


std::vector<Token> scan(const std::string& source);
std::vector<Statement*> parse(const std::vector<Token>& source);


// runs the languae
void run(const std::vector<Statement*>& statements);
void run(const std::string& source);


// interative init
void repl_init();

// source file init
void srcf_init(const int argc, const char** argv);