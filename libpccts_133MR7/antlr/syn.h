/*
 * syn.h
 *
 * $Id: syn.h,v 1.6 95/09/26 12:58:32 parrt Exp $
 * $Revision: 1.6 $
 *
 * This file includes definitions and macros associated with syntax diagrams
 *
 * SOFTWARE RIGHTS
 *
 * We reserve no LEGAL rights to the Purdue Compiler Construction Tool
 * Set (PCCTS) -- PCCTS is in the public domain.  An individual or
 * company may do whatever they wish with source code distributed with
 * PCCTS or the code generated by PCCTS, including the incorporation of
 * PCCTS, or its output, into commerical software.
 *
 * We encourage users to develop software with PCCTS.  However, we do ask
 * that credit is given to us for developing PCCTS.  By "credit",
 * we mean that if you incorporate our source code into one of your
 * programs (commercial product, research project, or otherwise) that you
 * acknowledge this fact somewhere in the documentation, research report,
 * etc...  If you like PCCTS and have developed a nice tool with the
 * output, please mention that you developed it using PCCTS.  In
 * addition, we ask that this header remain intact in our source code.
 * As long as these guidelines are kept, we expect to continue enhancing
 * this system and expect to make other tools available as they are
 * completed.
 *
 * ANTLR 1.33
 * Terence Parr
 * Parr Research Corporation
 * with Purdue University and AHPCRC, University of Minnesota
 * 1989-1995
 */

#include "set.h"

#define NumNodeTypes	4
#define NumJuncTypes	9

/* List the different node types */
#define nJunction		1
#define nRuleRef		2
#define nToken			3
#define nAction			4

/* Different types of junctions */
#define aSubBlk			1
#define aOptBlk			2
#define aLoopBlk		3
#define EndBlk			4
#define RuleBlk			5
#define Generic			6	/* just a junction--no unusual characteristics */
#define EndRule			7
#define aPlusBlk		8
#define aLoopBegin		9

typedef int NodeType;

#define TreeBlockAllocSize		500
#define JunctionBlockAllocSize	200
#define ActionBlockAllocSize	50
#define RRefBlockAllocSize		100
#define TokenBlockAllocSize		100

#ifdef __cplusplus
class ActionNode;
class Junction;
#endif

/* note that 'right' is used by the tree node allocator as a ptr for linked list */
typedef struct _tree {
			struct _tree *down, *right;
			int token;
			union {
				int rk;	/* if token==EpToken, => how many more tokens req'd */
				struct _tree *tref;	/* if token==TREE_REF */
				set sref;			/* if token==SET */
			} v;
#ifdef TREE_DEBUG
			int in_use;
#endif
		} Tree;

/* a predicate is defined to be a predicate action and a token tree with
 * context info (if used); later, this struct may include the
 * "hoisting distance" when we hoist past tokens.
 *
 * A tree is used to indicate && vs ||
 *
 *    p
 *    |
 *    q--r
 *
 * indicates p && (q||r).
 *
 * If expr is PRED_AND_LIST or PRED_OR_LIST, then it's an operation node
 * and indicates the start of an && or || list.
 */

typedef struct _Predicate {
	struct _Predicate *down, *right;	/* these have to be first */
	struct _Predicate *up, *left;		/* doubly-link me */
	char *expr;
	Tree *tcontext;	/* used if lookahead depth of > one is needed (tree) */
	int k;			/* lookahead depth for this tcontext */
	set scontext[2];/* used if lookahead depth of one is needed (set) */
					/* scontext[0] is not used; only needed so genExprSets()
					   routine works (it expects an array)
					 */
	set completion;	/* which lookahead depths are required to complete tcontext? */
#ifdef __cplusplus
	ActionNode *source;	/* where did this predicate come from? */
#else
	struct _anode *source;	/* where did this predicate come from? */
#endif
} Predicate;

typedef struct _ExceptionHandler {
			char *signalname;
			char *action;
		} ExceptionHandler;

typedef struct _ExceptionGroup {
			struct _ListNode *handlers; /* list of ExceptionHandler's */
			char *label;		/* label==""; implies not attached to any
								 * particular rule ref.
								 */
			char *altID;		/* which alt did it come from (blk#:alt#) */

            struct _ExceptionGroup  *pendingLink; /* for alternative EG MR7 */
            struct _ExceptionGroup  *outerEG;     /* for alternative EG MR7 */
            struct _LabelEntry      *labelEntry;  /* for alternative EG MR7 */
            int                     forRule;                         /* MR7 */
            int                     used;                            /* MR7 */
		} ExceptionGroup ;


#define TokenString(_i)			((TokenInd!=NULL)?TokenStr[TokenInd[_i]]:TokenStr[_i])
#define ExprString(_i)			((TokenInd!=NULL)?ExprStr[TokenInd[_i]]:ExprStr[_i])


				/* M e s s a g e  P a s s i n g  T o  N o d e s */

/*
 * assumes a 'Junction *r' exists.  This macro calls a function with
 * the pointer to the node to operate on and a pointer to the rule
 * in which it is enclosed.
 */
#define TRANS(p)	{if ( (p)==NULL ) fatal("TRANS: NULL object");		\
					if ( (p)->ntype == nJunction ) (*(fpJTrans[((Junction *)(p))->jtype]))( p );\
					else (*(fpTrans[(p)->ntype]))( p );}

#define PRINT(p)	{if ( (p)==NULL ) fatal("PRINT: NULL object");\
					(*(fpPrint[(p)->ntype]))( p );}

#define REACH(p,k,rk,a) {if ( (p)==NULL ) fatal("REACH: NULL object");\
					(a) = (*(fpReach[(p)->ntype]))( p, k, rk );}

#define TRAV(p,k,rk,a) {if ( (p)==NULL ) {\
					  if ( ContextGuardTRAV ) (a)=NULL; \
					  else fatal("TRAV: NULL object");\
				    } \
					else (a) = (*(fpTraverse[(p)->ntype]))( p, k, rk );}

/*
#define TRAV(p,k,rk,a) {if ( (p)==NULL ) fatal("TRAV: NULL object");\
					(a) = (*(fpTraverse[(p)->ntype]))( p, k, rk );}
*/

/* All syntax diagram nodes derive from Node -- superclass
 */
#ifdef __cplusplus
class Node {
public:
			NodeType ntype;
			char *rname;		/* what rule does this element live in? */
			int file;			/* index in FileStr */
			int line;			/* line number that element occurs on */
		};
#else
typedef struct _node {
			NodeType ntype;
			char *rname;		/* what rule does this element live in? */
			int file;			/* index in FileStr */
			int line;			/* line number that element occurs on */
		} Node;
#endif

#ifdef __cplusplus
class ActionNode : public Node {
public:
#else
typedef struct _anode {
			NodeType ntype;
			char *rname;		/* what rule does this action live in? */
			int file;			/* index in FileStr (name of file with action) */
			int line;			/* line number that action occurs on */
#endif
			Node *next;
			char *action;
			int is_predicate;	/* true if action is a <<...>>? predicate action */
			int done;			/* don't dump if action dumped (used for predicates) */
			int init_action;	/* is this the 1st action of 1st prod of block? */
			char *pred_fail;	/* what to do/print when predicate fails */
			Predicate *guardpred;	/* if '(context)? =>' was present, already done */
			unsigned char frmwarned;/* have we dumped a warning for pred yet? */
			unsigned char ctxwarned;/* have we dumped a warning for pred yet? */
#ifdef __cplusplus
		};
#else
		} ActionNode;
#endif

#ifdef __cplusplus
class TokNode : public Node {
public:
#else
typedef struct _toknode {
			NodeType ntype;
			char *rname;		/* name of rule it's in */
			int file;			/* index in FileStr (name of file with rule) */
			int line;			/* line number that token occurs on */
#endif
			Node *next;
			int token;
			int astnode;		/* leaf/root/excluded (used to build AST's) */
			unsigned char label;/* token label or expression ? */
			unsigned char remapped;
								/* used if token id's are forced to certain positions;
								 * a function walks the tree reassigning token numbers */
			unsigned char upper_range;
								/* used only if Token is of type T1..T2; in this case,
								 * use token..upper_range as the range; else
								 * upper_range must be 0 */
			unsigned char wild_card;
								/* indicates that the token is the "." wild-card;
								 * field token is ignored if wild_card is set
								 */
			unsigned int elnum; /* element number within the alternative */
#ifdef __cplusplus
			Junction *altstart;	/* pointer to node that starts alt */
#else
			struct _junct *altstart;	/* pointer to node that starts alt */
#endif
			struct _TCnode *tclass;		/* token class if tokclass ref */
			set tset;			/* set of tokens represented by meta token */
			char *el_label;		/* el_label:toknode */
			unsigned char complement;	/* complement the set? */
			ExceptionGroup *ex_group;	/* any exception[el_label] attached? */
            unsigned char use_def_MT_handler;
#ifdef __cplusplus
		};
#else
		} TokNode;
#endif

#ifdef __cplusplus
class RuleRefNode : public Node {
public:
#else
typedef struct _rrnode {
			NodeType ntype;
			char *rname;		/* name of rule it's in */
			int file;			/* index in FileStr (name of file with rule)
								   it's in */
			int line;			/* line number that rule ref occurs on */
#endif
			Node *next;
			char *text;			/* reference to which rule */
			char *parms;		/* point to parameters of rule invocation
								   (if present) */
			char *assign;		/* point to left-hand-side of assignment
								   (if any) */
			int linked;			/* Has a FoLink already been established? */
			int astnode;		/* excluded? (used to build AST's) */
			unsigned int elnum; /* element number within the alternative */
#ifdef __cplusplus
			Junction *altstart;
#else
			struct _junct *altstart;
#endif
			char *el_label;		/* el_label:rrnode */
			ExceptionGroup *ex_group;	/* any exception[el_label] attached? */
#ifdef __cplusplus
		};
#else
		} RuleRefNode;
#endif

#ifdef __cplusplus
class Junction : public Node {
public:
#else
typedef struct _junct {
			NodeType ntype;
			char *rname;		/* name of rule junction is in */
			int file;			/* index in FileStr (name of file with rule)
								   if blk == RuleBlk */
			int line;			/* line number that rule occurs on */
#endif
			char ignore;		/* used by FIRST computation to ignore
								   empty alt added for the (...)+ blks */
			char visited;		/* used by recursive routines to avoid
								   infinite recursion */
			char pvisited;		/* used by print routines to avoid
								   infinite recursion */
			char fvisited;		/* used by FoLink() to avoid
								   infinite recursion */
			char *lock;			/* used by REACH to track infinite recursion */
			char *pred_lock;	/* used by find_predicates to track infinite recursion */
			int altnum;			/* used in subblocks. altnum==0 means not an
								   alt of subrule */
			int jtype;			/* annotation for code-gen/FIRST/FOLLOW.
								   Junction type */
#ifdef __cplusplus
			Junction *end;		/* pointer to node with EndBlk in it
								   if blk == a block type */
#else
			struct _junct *end;	/* pointer to node with EndBlk in it
								   if blk == a block type */
#endif
			Node *p1, *p2;
			int halt;			/* never move past a junction with halt==TRUE */
			char *pdecl;		/* point to declaration of parameters on rule
								   (if present) */
			char *parm;			/* point to parameter of block invocation
								   (if present) */
			int predparm;		/* indicates that the 'parm' is a predicate
								 * to be used in the while loop generated
								 * for blocks */
			char *ret;			/* point to return type of rule (if present) */
			char *erraction;	/* point to error action (if present) */
			int blockid;		/* this is a unique ID */
			char *exception_label;	/* goto label for this alt */
			set *fset;			/* used for code generation */
			Tree *ftree;		/* used for code generation */
			Predicate *predicate;/* predicate that can be used to disambiguate */
			char guess;			/* true if (...)? block */
			char approx;		/* limit block to use linear approx lookahead? */
			set tokrefs;		/* if ith element of alt is tokref then i is member */
			set rulerefs;		/* if ith element of alt is rule ref then i is member */
			struct _ListNode *exceptions; /* list of exceptions groups for rule */
			struct _ListNode *el_labels;  /* list of element labels for rule */
            ExceptionGroup   *outerEG;                               /* MR7 */
            int              curAltNum;                              /* MR7 */
#ifdef __cplusplus
            Junction         *pendingLink;                           /* MR7 */
#else
            struct _junct    *pendingLink;                           /* MR7 */
#endif
#ifdef __cplusplus
		};
#else
		} Junction;
#endif

typedef struct { Node *left, *right;} Graph;

