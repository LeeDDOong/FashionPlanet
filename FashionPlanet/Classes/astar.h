#ifndef ASTAR_
//노드에 대한 정의
typedef struct node_s {
	int degree;                          //현재 이 노드의 깊이 값. 즉, 자료 구조 트리에서 깊이 값.
	int distance;                        //이 노드로부터 목적지까지의 거리
	int value_factor;                   //평가치 값( degree + distance )
	int x, y;                           //이 노드의 위치 (그리드의 위치) 
	struct node_s* direct[8];       //확장 가능한 8방향에 대한 노드
	struct node_s* prev_node;    //링크드 리스트 이전 노드 
	struct node_s* next_node;     //링크드 리스트 다음 노드 
} node_t;

//노드를 재정렬할 때 쓸 스택.
typedef struct node_stack_s {
	node_t*  node;                            //이 스택 위치에서 가리키고 있는 노드 
	struct node_stack_s*  next_node;    //이 스택의 다음 위치  
} node_stack_t;

#define ASTAR_XMAX		20
#define ASTAR_YMAX		20
typedef struct
{
	M_Int32 startX;
	M_Int32 startY;
	M_Int32 endX;
	M_Int32 endY;	
	M_Int32 mapData[ASTAR_XMAX][ASTAR_YMAX];
	node_t* best;
	
	
	int totalCnt;
	int tempX[128];
	int tempY[128];
	int bestX[128];
	int bestY[128];
	
} XASTAR;
extern XASTAR xAstar;

extern node_t *OPEN, *CLOSED;
extern node_stack_t* STACK;




void init_astar();
node_t* find_path(int start_x, int start_y, int dest_x, int dest_y);
M_Boolean setAstar(int startX,int startY,int endX,int endY,int type,int floor);
#endif



