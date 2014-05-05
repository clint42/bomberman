#include "Exception.hh"

AbstractVMException::AbstractVMException(std::string const &msg) throw() : _message(msg) {}
AbstractVMException::~AbstractVMException(void) throw() {}
std::string const &
AbstractVMException::message(void) const throw() { return this->_message; }

BadExpressionException::BadExpressionException(void) throw() : AbstractVMException("Bad Expression") {}
BadExpressionException::~BadExpressionException(void) throw() {}

UnknownInstructionException::UnknownInstructionException(std::string const &instruction) throw() : AbstractVMException("Unknown instruction \"" + instruction + "\"") {}
UnknownInstructionException::~UnknownInstructionException(void) throw() {}

OverFlowException::OverFlowException(void) throw() : AbstractVMException("Overflow") {}
OverFlowException::~OverFlowException(void) throw() {}

UnderFlowException::UnderFlowException(void) throw() : AbstractVMException("Underflow") {}
UnderFlowException::~UnderFlowException(void) throw() {}

EmptyStackException::EmptyStackException(void) throw() : AbstractVMException("Empty stack") {}
EmptyStackException::~EmptyStackException(void) throw() {}

ImpossibleOperationException::ImpossibleOperationException(void) throw() : AbstractVMException("Division/Modulo by zero") {}
ImpossibleOperationException::~ImpossibleOperationException(void) throw() {}

UnverifiedAssertInstructionException::UnverifiedAssertInstructionException(void) throw() : AbstractVMException("Assert instruction not verified") {}
UnverifiedAssertInstructionException::~UnverifiedAssertInstructionException(void) throw() {}

NoEnoughOperandsException::NoEnoughOperandsException(std::string const &operation) throw() : AbstractVMException("No enough operands for " + operation + " operation") {}
NoEnoughOperandsException::~NoEnoughOperandsException(void) throw() {}

InvalidArgNumberException::InvalidArgNumberException(std::string const &instruction) throw() : AbstractVMException("Invalid arguments number for instruction: \"" + instruction + "\"") {}
InvalidArgNumberException::~InvalidArgNumberException(void) throw() {}

CantOpenFile::CantOpenFile(std::string const &file) throw() : AbstractVMException("Can't open file: \"" + file + "\"") {}
CantOpenFile::~CantOpenFile(void) throw() {}

ProgHaveNotExit::ProgHaveNotExit(std::string const &prog) throw() : AbstractVMException("Program: \"" + prog + "\" haven't exit instruction") {}
ProgHaveNotExit::~ProgHaveNotExit(void) throw() {}
