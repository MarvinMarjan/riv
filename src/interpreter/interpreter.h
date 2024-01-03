#pragma once

#include <vector>
#include <filesystem>

#include <statement/statement.h>
#include <expression/expression.h>
#include <environment/environment.h>



struct Exception;


// interpret statements
class Interpreter : public ExpressionProcessor, public StatementProcessor
{
public:
	Interpreter();


	void interpret(const std::vector<Statement*>& statements);


	void set_repl_mode(const bool enable) noexcept { repl_mode_ = enable; }

	bool repl_mode() const noexcept { return repl_mode_; }


	Environment* global = nullptr;
	Environment* environment = nullptr;


private:
	friend class RivFunction;


	struct ScopeConfig
	{
		ScopeConfig() = default;
		ScopeConfig(Environment* const old_env, Environment* const new_env)
				: old_env(old_env), new_env(new_env) {}

		Environment* old_env = nullptr;
		Environment* new_env = nullptr;
	};



	// Statements

	void process_expression (ExpressionStatement&) override;
	void process_block      (BlockStatement     &) override;
	void process_print      (PrintStatement     &) override;
	void process_var        (VarStatement       &) override;
	void process_if         (IfStatement        &) override;
	void process_while      (WhileStatement     &) override;
	void process_break      (BreakStatement     &) override;
	void process_continue   (ContinueStatement  &) override;
	void process_function   (FunctionStatement  &) override;
	void process_return     (ReturnStatement    &) override;
	void process_import     (ImportStatement    &) override;
	void process_package    (PackageStatement   &) override;

	void execute_block(const std::vector<Statement*>& statements, const ScopeConfig& config);

	void execute(Statement* const statement) {
		statement->process(*this);
	}



	// Expressions

	Type process_binary            (BinaryExpression           &) override;
	Type process_unary             (UnaryExpression            &) override;
	Type process_grouping          (GroupingExpression         &) override;
	Type process_literal           (LiteralExpression          &) override;
	Type process_literal_array     (LiteralArrayExpression     &) override;
	Type process_indexing          (IndexingExpression         &) override;
	Type process_identifier        (IdentifierExpression       &) override;
	Type process_assignment        (AssignmentExpression       &) override;
	Type process_call              (CallExpression             &) override;
	Type process_package_resolution(PackageResolutionExpression&) override;
	Type process_ternary           (TernaryExpression          &) override;


	Type evaluate(Expression* expr);



	// Statement Utilities


	static bool check_import_file_without_extension(std::filesystem::path& path) noexcept;
	static std::filesystem::path get_path_from_import_symbols(const std::vector<Token>& symbols);

	void import_file(const std::string& path) noexcept;
	void import_dir (const std::string& path) noexcept;
	void import_lib (const std::string& path) noexcept;



	// Expression Utilities


	Type assign_variable                   (const Token& identifier, const Type& value);
	Type assign_package_member             (AssignmentExpression& assignment_expression, PackageResolutionExpression* package_expression);
	Type assign_array_item                 (AssignmentExpression& assignment_expression, IndexingExpression* indexing);

	Type get_package_object_from_expression(PackageResolutionExpression& package_expression);

	Type call_function(Type& callee, const std::vector<Type>& arguments, const TokenPosition& paren_pos);
	Type call_symbol  (Type& callee, const std::vector<Type>& arguments, const TokenPosition& paren_pos);




	static bool are_values_of_type(const std::initializer_list<Type>& values, TypeIndex type) noexcept;

	static void throw_if_type_differs(const std::initializer_list<Type>& values, TypeIndex type, const Exception& err);


	bool importing_ = false;
	bool repl_mode_ = false;
};