#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
 int kuser_, knice_, ksystem_, kidle_, kiowait_, kirq_, ksoftirq_, ksteal_, kguest_, kguestnice_;
};

#endif