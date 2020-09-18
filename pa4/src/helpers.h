/****************Structs********************/
typedef struct var{
	char name[17];
	int value; //0 or 1
	struct var* next;
	
}variable;

typedef enum { AND, OR, NAND, NOR, XOR, NOT, PASS, DECODER, MULTIPLEXER } gates;
typedef struct gate {
	gates type;
	int size; // indicates size of DECODER and MULTIPLEXER
	variable** inputs;
	variable** selectors;
	variable* outputs;
	struct gate* next;
					// includes inputs and outputs, indicated by variable numbers
} gate;
/****************Function Prototypes********************/
void ptable(variable* inputs, int numIn,variable* outputs, int numOut);
void reset(variable* inputs,int numIn);
void tobinary(variable* inputs, int numIn, int index);
int searchInputVars(variable* inputs, int numIn, char* input);
int searchOutputVars(variable* outputs, int numOut, char* output);
variable* returnVar(char* name,variable* inputs,variable* outputs,variable* temps, int numIn, int numOut,variable* head);
void not(variable* input,variable* output);
void and(variable* input1,variable* input2,variable* output);
void or(variable* input1,variable* input2,variable* output);
void nand(variable* input1,variable* input2,variable* output);
void nor(variable* input1,variable* input2,variable* output);
void xor(variable* input1,variable* input2,variable* output);
void multiplexer(gate* gate);
void pass(variable* input,variable* output);
void decoder(gate* gate);
/*******************************************************/
