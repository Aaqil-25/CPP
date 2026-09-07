

## ex00 — Bureaucrat: line-by-line explanation

### `Bureaucrat.hpp` (the header / the "contract")

```1:12:d:\42\CPP-main\cpp05\ex00\Bureaucrat.hpp
#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat
{
	private:
		std::string const	name;
		int					grade;
```

- `#ifndef / #define / #endif` — **include guard**. If this header gets included twice, the second time `BUREAUCRAT_HPP` is already defined, so the whole file is skipped. This prevents "double inclusion" (which the subject says gives you a 0 if you get it wrong).
- The three `#include`s pull in everything this header *itself* needs: `std::string`, `std::cout`/`std::ostream`, and `std::exception`. The rule is: a header must include its own dependencies.
- `std::string const name;` — the name is `const` because the subject says "A constant name." A `const` member can only be set in the **constructor initializer list**, never assigned later.
- `int grade;` — grade 1 (highest) to 150 (lowest).

```13:24:d:\42\CPP-main\cpp05\ex00\Bureaucrat.hpp
	public:
		Bureaucrat();
		Bureaucrat(std::string const & name, int grade);
		Bureaucrat(const Bureaucrat& other);
		Bureaucrat& operator=(const Bureaucrat& other);
		~Bureaucrat();

		std::string const &	getName() const;
		int					getGrade() const;

		void	incrementGrade();
		void	decrementGrade();
```

- The first four + destructor are the **Orthodox Canonical Form** (default ctor, parameterized ctor, copy ctor, copy assignment, destructor). The subject requires OCF for every class except the exception classes.
- `getName()`/`getGrade()` are the required getters. They're `const` because reading a value shouldn't modify the object. `getName` returns `const &` to avoid copying the string.
- `incrementGrade`/`decrementGrade` change the grade and may throw.

```26:38:d:\42\CPP-main\cpp05\ex00\Bureaucrat.hpp
		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);
```

- These are **nested exception classes** — that's why the subject calls them `Bureaucrat::GradeTooHighException`. They inherit from `std::exception` so a `catch (std::exception & e)` can catch them (as shown in the subject's example).
- `what()` is the virtual function from `std::exception` that returns the error message. `const throw()` is the exact C++98 signature: `const` (doesn't modify) and `throw()` (promises to throw nothing itself).
- `operator<<` is declared **outside** the class (a free function) because the left operand is the stream (`std::cout`), not a Bureaucrat.

### `Bureaucrat.cpp` (the implementation)

```8:17:d:\42\CPP-main\cpp05\ex00\Bureaucrat.cpp
Bureaucrat::Bureaucrat(std::string const & name, int grade) : name(name)
{
	std::cout << "Bureaucrat constructor called" << std::endl;
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	this->grade = grade;
}
```

- `: name(name)` — the initializer list. The `const` name **must** be set here. We can't validate the name, but we can validate the grade.
- If `grade < 1` it's too high (grade 1 is the max), so we `throw` a `GradeTooHighException`. If `grade > 150` it's too low. `throw` immediately stops the constructor — the object is never fully created.
- Only if both checks pass do we store the grade.

```47:59:d:\42\CPP-main\cpp05\ex00\Bureaucrat.cpp
void Bureaucrat::incrementGrade()
{
	if (this->grade - 1 < 1)
		throw Bureaucrat::GradeTooHighException();
	this->grade--;
}

void Bureaucrat::decrementGrade()
{
	if (this->grade + 1 > 150)
		throw Bureaucrat::GradeTooLowException();
	this->grade++;
}
```

- **This is the trickiest part.** Grade 1 is the *highest*, 150 the *lowest*. "Incrementing" a bureaucrat's importance means the number goes **down** (grade 3 → grade 2). So `incrementGrade` does `grade--`.
- Before decrementing the number, we check: would it drop below 1? If so, throw `GradeTooHighException`.
- `decrementGrade` does the opposite: `grade++`, and guards against going above 150.

```61:69:d:\42\CPP-main\cpp05\ex00\Bureaucrat.cpp
const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Grade is too high (must be >= 1)";
}
```

- Defines the message returned when you call `e.what()` in the catch block. Returns a C-string literal (that's what `std::exception::what` returns).

```71:75:d:\42\CPP-main\cpp05\ex00\Bureaucrat.cpp
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
	return os;
}
```

- Prints exactly the format the subject asks for: `<name>, bureaucrat grade <grade>.` It returns the stream so you can chain (`std::cout << b << std::endl`).

The output confirms everything: valid grades print correctly, all 4 out-of-range cases throw and are caught. Notice in Test 4 the destructor runs *before* the catch prints — that's **stack unwinding** (the local object is destroyed as the exception propagates out of the `try`).

Now let me build **ex01**.

ex01 adds a `Form` class and gives `Bureaucrat` a `signForm()` method. Let me create the ex01 folder (Bureaucrat files carried over + new Form files).

ex01 compiles clean and works. Let me explain the **new** parts (I won't repeat the Bureaucrat basics).

## ex01 — Form + signForm

### The circular-dependency problem (important!)

`Bureaucrat` needs to know about `Form` (for `signForm`), and `Form` needs to know about `Bureaucrat` (for `beSigned`). If each header `#include`s the other, you get an infinite include loop. The fix is a **forward declaration**:

```9:9:d:\42\CPP-main\cpp05\ex01\Bureaucrat.hpp
class Form;
```

- This tells the compiler "`Form` is a class that exists somewhere" — enough to declare `void signForm(Form& form);` because a **reference** doesn't need the full definition. The full `#include "Form.hpp"` goes in the `.cpp` where we actually *use* Form's members. `Form.hpp` does the mirror-image with `class Bureaucrat;`.

### `Form.hpp` attributes

```12:15:d:\42\CPP-main\cpp05\ex01\Form.hpp
		std::string const	name;
		bool				isSigned;
		int const			gradeToSign;
		int const			gradeToExecute;
```

- Exactly what the subject lists: constant name, a signed flag (`false` at construction), and two **const** grades. All private. The grades are `const` because a form's requirements never change once created.

### The constructor validates grades

```8:16:d:\42\CPP-main\cpp05\ex01\Form.cpp
Form::Form(std::string const & name, int gradeToSign, int gradeToExecute)
	: name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
	std::cout << "Form constructor called" << std::endl;
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw Form::GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw Form::GradeTooLowException();
}
```

- Same grade rules as Bureaucrat, but applied to **both** grades. Note the initializer list runs *first* (const members must be set), then we validate and throw if needed.

### `beSigned` — the form checks the bureaucrat

```59:64:d:\42\CPP-main\cpp05\ex01\Form.cpp
void Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > this->gradeToSign)
		throw Form::GradeTooLowException();
	this->isSigned = true;
}
```

- Remember a **higher number = lower rank**. So the bureaucrat can sign only if their grade number is `<=` the required one. If their number is *greater* (rank too low), we throw. Otherwise the form becomes signed.

### `signForm` — the bureaucrat asks the form, and reports

```61:75:d:\42\CPP-main\cpp05\ex01\Bureaucrat.cpp
void Bureaucrat::signForm(Form& form)
{
	try
	{
		form.beSigned(*this);
		std::cout << this->name << " signed " << form.getName() << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << this->name << " couldn't sign " << form.getName()
			<< " because " << e.what() << "." << std::endl;
	}
}
```

- The bureaucrat calls `form.beSigned(*this)` (`*this` = "me, this bureaucrat"). If it succeeds, print `<name> signed <form>`. If `beSigned` throws, we catch it here and print the `couldn't sign ... because ...` message using `e.what()` as the reason. This matches the subject exactly.

The output confirms: Alice (grade 1) signs, Bob (grade 100) can't sign a grade-50 form, invalid-grade form throws, and Carol at exactly grade 50 succeeds (boundary case).

Now **ex02** — the biggest one. Let me build it.

ex02 renames `Form` → `AForm` (abstract), adds the `execute()` logic, and three concrete forms. Let me build all the files.

Now the Bureaucrat (with `executeForm`):

Now the three concrete forms:

Everything compiles and works. One thing: in Test 1 the gardener (grade 140) could **sign** but not **execute** (needs 137), so no file was created — that actually correctly demonstrates the grade check, but let me adjust the test so we also see the shrubbery file get written.

ex02 works fully — the shrubbery file is generated with ASCII trees. Let me explain the key new concepts.

## ex02 — Abstract form + polymorphic execution

### Why `AForm` is *abstract*

```17:19:d:\42\CPP-main\cpp05\ex02\AForm.hpp
	protected:
		virtual void	executeAction() const = 0;
```

- The `= 0` makes `executeAction` a **pure virtual function**. A class with at least one pure virtual function is **abstract** — you cannot create an `AForm` directly (`AForm f;` won't compile). You can only create objects of concrete subclasses that *implement* `executeAction`. That's exactly what the subject demands ("the base class Form must be an abstract class and should therefore be renamed AForm").
- It's `protected` so only the class and its children can call it — outsiders go through `execute()` instead.

### The "elegant" design (Template Method pattern)

The subject hints: *"Whether you check the requirements in every concrete class or in the base class ... one way is more elegant."* The elegant way is to check **once** in the base class:

```66:73:d:\42\CPP-main\cpp05\ex02\AForm.cpp
void AForm::execute(Bureaucrat const & executor) const
{
	if (!this->isSigned)
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > this->gradeToExecute)
		throw AForm::GradeTooLowException();
	this->executeAction();
}
```

- `execute()` (in the base, shared by all forms) does the two universal checks: is the form signed? Is the executor's grade high enough? If either fails, it throws. Only if both pass does it call `this->executeAction()`.
- Because `executeAction()` is **virtual**, `this->executeAction()` calls the *correct* subclass version at runtime (Shrubbery vs Robotomy vs Presidential). This is **polymorphism**. We wrote the checks once and never repeat them.

### A concrete form: constructor chaining

```9:13:d:\42\CPP-main\cpp05\ex02\ShrubberyCreationForm.cpp
ShrubberyCreationForm::ShrubberyCreationForm(std::string const & target)
	: AForm("ShrubberyCreationForm", 145, 137), target(target)
{
	std::cout << "ShrubberyCreationForm constructor called" << std::endl;
}
```

- `: AForm("ShrubberyCreationForm", 145, 137)` calls the **base class constructor** first, passing the fixed name and the required grades (145 to sign, 137 to execute — straight from the subject). Then `target(target)` stores the target. The subject says each concrete form takes only the target as a parameter, which is exactly what we do.

### Copy assignment calls the base version

```21:31:d:\42\CPP-main\cpp05\ex02\ShrubberyCreationForm.cpp
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	std::cout << "ShrubberyCreationForm copy assignment operator called" << std::endl;
	if (this != &other)
	{
		AForm::operator=(other);
		this->target = other.target;
	}
	return *this;
}
```

- `AForm::operator=(other)` copies the base part (the `isSigned` flag; the const name/grades can't change), then we copy the `target`. This keeps the "canonical form" complete across the inheritance chain.

### The three actions

- **Shrubbery** (`executeAction`) opens `<target>_shrubbery` with `std::ofstream` and writes ASCII trees.
- **Robotomy** prints drilling noises, then `std::rand() % 2` gives a 50/50 success/fail. We seed once with `std::srand(std::time(NULL))` in `main`.
- **Presidential** prints that the target was pardoned by Zaphod Beeblebrox.

### `virtual ~AForm()` — critical for inheritance

The base destructor is `virtual`. When you delete a concrete form through an `AForm*` pointer (which we do in ex03), the virtual destructor ensures the *derived* destructor runs too — no memory leak. The output shows the full chain: `ShrubberyCreationForm destructor` → `AForm destructor`.

Now the final one, **ex03 — Intern**.

ex03 reuses all ex02 files and adds the `Intern`. Let me copy the ex02 sources into ex03, then add the Intern class.

All four exercises compile with zero warnings and run correctly. Let me do a final memory-leak check on ex03 (it uses `new`/`delete`).

Valgrind isn't installed, but the memory handling is provably correct: every `new` from `makeForm` is matched by a `delete` in `main`, and in Test 4 the exception is thrown *before* any allocation, so nothing leaks.

Let me finalize the todos and explain ex03.

## ex03 — Intern (no ugly if/else chains)

The subject explicitly warns: *"You must avoid unreadable and messy solutions, such as using an excessive if/elseif/else structure. This kind of approach will not be accepted."* So instead of `if (name == "...") ... else if ...`, I used two parallel arrays: names and **function pointers**.

### The static builder functions

```28:41:d:\42\CPP-main\cpp05\ex03\Intern.cpp
AForm* Intern::makeShrubbery(std::string const & target)
{
	return new ShrubberyCreationForm(target);
}

AForm* Intern::makeRobotomy(std::string const & target)
{
	return new RobotomyRequestForm(target);
}

AForm* Intern::makePresidential(std::string const & target)
{
	return new PresidentialPardonForm(target);
}
```

- Each one `new`s one concrete form and returns it as an `AForm*` (upcasting a derived pointer to a base pointer — always safe). They're `static` because they don't need any Intern instance data — they're just factory helpers.

### `makeForm` — the clean lookup

```44:69:d:\42\CPP-main\cpp05\ex03\Intern.cpp
AForm* Intern::makeForm(std::string const & formName, std::string const & target)
{
	std::string const	names[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};
	AForm* (*builders[3])(std::string const &) = {
		&Intern::makeShrubbery,
		&Intern::makeRobotomy,
		&Intern::makePresidential
	};

	for (int i = 0; i < 3; i++)
	{
		if (names[i] == formName)
		{
			std::cout << "Intern creates " << formName << std::endl;
			return builders[i](target);
		}
	}
	std::cout << "Error: form \"" << formName << "\" does not exist." << std::endl;
	throw Intern::FormNotFoundException();
}
```

- `names[3]` holds the recognized form names. `builders[3]` is an **array of function pointers**. The scary-looking type `AForm* (*builders[3])(std::string const &)` reads as: "an array of 3 pointers to functions that take a `std::string const &` and return `AForm*`". Index `i` in `names` lines up with index `i` in `builders`.
- The loop compares `formName` against each name. On a match it prints `Intern creates <form>` (exactly as the subject asks) and calls `builders[i](target)` — which dispatches to the right factory and returns the new form.
- If nothing matches, it prints an explicit error and throws. Adding a new form later means just adding one entry to each array — no growing if/else. This is the "elegant" solution the evaluators want.

### `main` and ownership

```13:19:d:\42\CPP-main\cpp05\ex03\main.cpp
		AForm* rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		Bureaucrat boss("Boss", 1);
		boss.signForm(*rrf);
		boss.executeForm(*rrf);
		delete rrf;
```

- `makeForm` returns a **heap pointer** (created with `new`), so the caller owns it and must `delete rrf` — this is why the base class destructor had to be `virtual` (so `delete rrf`, which is an `AForm*`, correctly runs the `RobotomyRequestForm` destructor). The output shows the full destructor chain, confirming no leak.

---

## Summary

All four exercises are complete, compile with `c++ -Wall -Wextra -Werror -std=c++98` (zero warnings), and run correctly:

| Exercise | Directory | Key concept |
|----------|-----------|-------------|
| ex00 | `cpp05/ex00` | Custom exceptions, throw/catch, nested exception classes |
| ex01 | `cpp05/ex01` | Forward declarations, class interaction, `beSigned`/`signForm` |
| ex02 | `cpp05/ex02` | Abstract class, pure virtual, polymorphism, Template Method pattern |
| ex03 | `cpp05/ex03` | Factory via function-pointer arrays, heap ownership, virtual destructors |

**Core C++ ideas this module teaches you:**
- **Exceptions**: `throw` an object, unwind the stack (destructors run automatically), `catch` by reference to a base (`std::exception&`).
- **Orthodox Canonical Form** for every class (except exception classes, per the subject).
- **Include guards + forward declarations** to manage dependencies and break cycles.
- **Abstract classes & polymorphism**: the base defines the workflow (`execute`), subclasses fill in the behavior (`executeAction`).

A couple of things worth knowing for your **defense** (they often ask you to modify something live):
- The grade logic is inverted (1 = highest). Be ready to explain why `incrementGrade` does `grade--`.
- Be ready to explain why the destructor is `virtual` and what would leak without it.
- Be ready to add a *fourth* form — with the function-pointer array design it's a 2-line change in `Intern.cpp`, which is a great thing to demonstrate.

Want me to add extra edge-case tests, or walk through any specific concept (e.g., stack unwinding or function pointers) in more depth?

---

**User**

<timestamp>Monday, Sep 7, 2026, 11:00 PM (UTC+4)</timestamp>
<system_notification>
The following task has finished. If you were already aware, ignore this notification and do not restate prior responses.

<task>
kind: shell
status: success
task_id: 603258
title: Check other compilers
tool_call_id: toolu_01ACDKF1NLZdZRQpBGFe9s5C
output_path: C:\Users\Aaqil\.cursor\projects\d-42-CPP-main-cpp05\terminals\603258.txt
</task>
</system_notification>

<timestamp>Monday, Sep 7, 2026, 11:00 PM (UTC+4)</timestamp>
<system_notification>
The following task has finished. If you were already aware, ignore this notification and do not restate prior responses.

<task>
kind: shell
status: success
task_id: 603259
title: Check WSL compiler availability
tool_call_id: toolu_01NzfxuTLBQfhpeKfx87hWaq
output_path: C:\Users\Aaqil\.cursor\projects\d-42-CPP-main-cpp05\terminals\603259.txt
</task>
</system_notification>

<timestamp>Monday, Sep 7, 2026, 11:00 PM (UTC+4)</timestamp>
<system_notification>
The following task has finished. If you were already aware, ignore this notification and do not restate prior responses.

<task>
kind: shell
status: success
task_id: 603260
title: Compile and run ex01 in WSL
tool_call_id: toolu_014j64DBjdV6YDRUAhAE25NF
output_path: C:\Users\Aaqil\.cursor\projects\d-42-CPP-main-cpp05\terminals\603260.txt
</task>
</system_notification>

<timestamp>Monday, Sep 7, 2026, 11:00 PM (UTC+4)</timestamp>
<system_notification>
The following task has finished. If you were already aware, ignore this notification and do not restate prior responses.

<task>
kind: shell
status: error
task_id: 603261
title: Compile and run ex02 in WSL
tool_call_id: toolu_01L6TVbpUeT2UDZmnKLvomvV
detail: exit_code=1
output_path: C:\Users\Aaqil\.cursor\projects\d-42-CPP-main-cpp05\terminals\603261.txt
</task>
</system_notification>

<timestamp>Monday, Sep 7, 2026, 11:00 PM (UTC+4)</timestamp>
<system_notification>
The following task has finished. If you were already aware, ignore this notification and do not restate prior responses.

<task>
kind: shell
status: success
task_id: 603262
title: Rebuild ex02 and show shrubbery file
tool_call_id: toolu_01Lbu9HEzbNVXzV8vFHXdWnv
output_path: C:\Users\Aaqil\.cursor\projects\d-42-CPP-main-cpp05\terminals\603262.txt
</task>
</system_notification>

<timestamp>Monday, Sep 7, 2026, 11:00 PM (UTC+4)</timestamp>
<system_notification>
The following task has finished. If you were already aware, ignore this notification and do not restate prior responses.

<task>
kind: shell
status: success
task_id: 603263
title: Copy ex02 sources into ex03
tool_call_id: toolu_01FhoC5KMWtjPpk49oHEtgsa
output_path: C:\Users\Aaqil\.cursor\projects\d-42-CPP-main-cpp05\terminals\603263.txt
</task>
</system_notification>

<timestamp>Monday, Sep 7, 2026, 11:00 PM (UTC+4)</timestamp>
<system_notification>
The following task has finished. If you were already aware, ignore this notification and do not restate prior responses.

<task>
kind: shell
status: success
task_id: 603264
title: Compile and run ex03 in WSL
tool_call_id: toolu_01UXnFKnQFwuVfyKQjGnwYu1
output_path: C:\Users\Aaqil\.cursor\projects\d-42-CPP-main-cpp05\terminals\603264.txt
</task>
</system_notification>
<user_query>Briefly inform the user about the task result and perform any follow-up actions (if needed).</user_query>

---

**Cursor**

All tasks finished successfully. The one "error" notification (ex02, task 603261) was just the initial run where `cat garden_shrubbery` failed because the gardener's grade was too low to execute the form — I already diagnosed that, lowered the grade to 130, and reran successfully, so the shrubbery file now generates correctly.

**Final status — all 4 exercises done and verified:**
- **ex00, ex01, ex02, ex03** all compile with `c++ -Wall -Wextra -Werror -std=c++98` (zero warnings) and run correctly in WSL.
- No memory leaks by construction (every `new` in `Intern::makeForm` is matched by a `delete`, virtual destructors in place).

No follow-up actions needed. If you'd like, I can add more edge-case tests, or go deeper on any concept (stack unwinding, function pointers, or the abstract-class/polymorphism mechanics) for your peer evaluation.

