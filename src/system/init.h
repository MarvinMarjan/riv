#pragma once

#include <string>
#include <vector>



enum class InitMode
{
	REPL,
	SourceFile
};


InitMode get_init_mode(int argc, const char** argv) noexcept;


struct Token;

class Statement;


std::vector<Token>      scan (const std::string       & source);
std::vector<Statement*> parse(const std::vector<Token>& source, bool repl_mode = false);


// runs the language from a source
void run(const std::vector<Statement*>& statements);
void run(const std::string& source);


// interactive init
void repl_init(int argc, const char** argv);

// source file init
void src_file_init(int argc, const char** argv);