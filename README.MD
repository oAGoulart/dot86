[![dot86](banner.png)]()

This assignment consists of the implementation of the data path of a processor (e.g., MIPS unicycle or multicycle) to simulate the execution of an assembly language program according to the instruction set of the architecture defined by the students.

Therefore, this assignment is divided into two steps:

**Step 1**
1. Definition of the architecture instruction set. That is, which instructions the architecture will be able to execute and their classification into classes. Also define how to be the size of instructions, in bits. What will the format of the instructions look like? How will the memory address be. Among other details regarding ISA.
2. Implementation of architecture components in the Logisim tool: Program Counter, Instruction Memory, Control Unit, Register Bank, ALU, Data Memory and additional components. There is no need to have all components implemented at the time of delivery of the first stage. However, please note that the assessment will consider the evolution of the work to date and the potential for carrying out the work for step 2.
3. Implementation of the control unit (at least the state machine with the idea of how the architecture works).
4. At this stage, the architecture must be capable of, at least:

    1. read an instruction from instruction memory;
    2. refresh the PC to fetch the next instruction;
    3. interpret the instruction bits to define how the architecture will behave with respect to the instruction.

Any interpretation beyond the minimum will count as a “plus” in the evaluation.

**Step 2**
1. Implementation of the rest of the architecture data path.
2. Implementation of an algorithm using the instruction set of the defined architecture.
3. Simulation of the algorithm execution in the proposed architecture, validating the architecture and the architecture instruction set.
4. Delivery of the final report containing the description of the architecture and ISA.
5. Delivery of files developed in logisim.

## Documentation

Take a look at the [docs](https://oagoulart.github.io/dot86/).
