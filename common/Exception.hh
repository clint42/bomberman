#ifndef EXCEPTION_HH_
# define EXCEPTION_HH_

# include <exception>
# include <string>

class AbstractVMException : public std::exception
{
private:
  std::string	_message;

public:
  AbstractVMException(std::string const &) throw();
  virtual ~AbstractVMException(void) throw();

  virtual std::string const &message(void) const throw();
};

class BadExpressionException : public AbstractVMException
{
public:
  BadExpressionException(void) throw();
  virtual ~BadExpressionException(void) throw();
};

class UnknownInstructionException : public AbstractVMException
{
public:
  UnknownInstructionException(std::string const &) throw();
  virtual ~UnknownInstructionException(void) throw();
};

class OverFlowException : public AbstractVMException
{
public:
  OverFlowException(void) throw();
  virtual ~OverFlowException(void) throw();
};

class UnderFlowException : public AbstractVMException
{
public:
  UnderFlowException(void) throw();
  virtual ~UnderFlowException(void) throw();
};

class EmptyStackException : public AbstractVMException
{
public:
  EmptyStackException(void) throw();
  virtual ~EmptyStackException(void) throw();
};

class ImpossibleOperationException : public AbstractVMException
{
public:
  ImpossibleOperationException(void) throw();
  virtual ~ImpossibleOperationException(void) throw();
};

class UnverifiedAssertInstructionException : public AbstractVMException
{
public:
  UnverifiedAssertInstructionException(void) throw();
  virtual ~UnverifiedAssertInstructionException(void) throw();
};

class NoEnoughOperandsException : public AbstractVMException
{
public:
  NoEnoughOperandsException(std::string const &) throw();
  virtual ~NoEnoughOperandsException(void) throw();
};

class InvalidArgNumberException : public AbstractVMException
{
public:
  InvalidArgNumberException(std::string const &) throw();
  virtual ~InvalidArgNumberException(void) throw();
};

class CantOpenFile : public AbstractVMException
{
public:
  CantOpenFile(std::string const &) throw();
  virtual ~CantOpenFile(void) throw();
};

class ProgHaveNotExit : public AbstractVMException
{
public:
  ProgHaveNotExit(std::string const &) throw();
  virtual ~ProgHaveNotExit(void) throw();
};

#endif
