#pragma once
#ifndef _PIPE_ELEMENT_H

struct PipeElement;

struct IPipe {
	virtual ~IPipe() {};
	virtual const PipeElement* GetElement(int x, int y) const = 0;
	virtual bool IsPipeOk() const = 0;
	virtual void SetElement(PipeElement* element) = 0;
	virtual int GetSize() const = 0;
};

struct PipeElement {
	virtual ~PipeElement() {};
	virtual bool IsConnectedCorrectly(const IPipe* pipe) const = 0;
	int m_x;
	int m_y;
};

class Pipe : public IPipe {
 public:
	 Pipe(int size);
	 ~Pipe();
	 const PipeElement* GetElement(int x, int y) const override;
	 bool IsPipeOk() const override;
	 void SetElement(PipeElement* element) override;
	 int GetSize() const override;
 private:
	 int m_size;
	 PipeElement*** m_array;
};

//---------------

class PipeElementMinus : public PipeElement {
 public:
 	 PipeElementMinus(int x, int y, IPipe* pipe);
	 ~PipeElementMinus();
	 bool IsConnectedCorrectly(const IPipe* pipe) const override;
};

class PipeElementI : public PipeElement {
 public:
	 PipeElementI(int x, int y, IPipe* pipe);
	 ~PipeElementI();
	 bool IsConnectedCorrectly(const IPipe* pipe) const override;
};

class PipeElementPlus : public PipeElement{
 public:
	 PipeElementPlus(int x, int y, IPipe* pipe);
	 ~PipeElementPlus();
	 bool IsConnectedCorrectly(const IPipe* pipe) const override;
};

class PipeElementO : public PipeElement {
 public:
	 PipeElementO(int x, int y, IPipe* pipe);
	 ~PipeElementO();
	 bool IsConnectedCorrectly(const IPipe* pipe) const override;
};

class PipeElementT : public PipeElement {
 public:
	 PipeElementT(int x, int y, IPipe* pipe);
	 ~PipeElementT();
	 bool IsConnectedCorrectly(const IPipe* pipe) const override;
};

#endif // !_PIPE_ELEMENT_H