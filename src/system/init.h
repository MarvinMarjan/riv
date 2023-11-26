#pragma once



enum class InitMode
{
	REPL,
	SourceFile
};



// gets the initialization mode
InitMode get_init_mode(const int argc, const char** argv) noexcept;



// interative init
void repl_init();

// source file init
void srcf_init(const int argc, const char** argv);