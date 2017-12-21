/************************************************************************************************************/
/* Description : A star algorithm sample code.                                                                   */
/* File Name : astar.cpp                                                                                                */
/* Date: author : DEC/18/2009                                                                                       */
/* Author: Hermet (hermet@naver.com)                                                                           */
/************************************************************************************************************/
//http://blog.naver.com/hermet?Redirect=Log&logNo=95405999

#include "Global.h"


XASTAR xAstar;



enum { DIRECTION_LEFT, DIRECTION_LEFTUP, DIRECTION_UP, DIRECTION_RIGHTUP,  DIRECTION_RIGHT, 
          DIRECTION_RIGHTDOWN, DIRECTION_DOWN, DIRECTION_LEFTDOWN };

node_t *OPEN, *CLOSED;
node_stack_t* STACK;

const int FINDPATH_LIMIT = 200;         

 
void init_astar() {
	
	node_t* temp;
	node_stack_t* stack;

	while(OPEN) {
		temp = OPEN->next_node;
		free(OPEN);
		OPEN = temp;

	}

	while(CLOSED) {
		temp = CLOSED->next_node;
		free(CLOSED);
		CLOSED = temp;
	}
	
	while(STACK) {
		stack = STACK->next_node;
		free(STACK);
		STACK = stack;
	}

}


 
bool is_available_grid( int x, int y )  {
 
	
	if(xAstar.mapData[x][y] == TRUE)
		return 0;

	return 1;

}


 
node_t* is_open(int x, int y) {
	
	node_t *temp = OPEN;

	while(temp) {
		if(temp->x==x && temp->y==y) 
			return temp;		
		temp = temp->next_node;
	}

	return NULL;
}


 
node_t* is_closed(int x, int y) {
	
	node_t *temp = CLOSED;

	while(temp) {
		if(temp->x==x && temp->y==y) 
			return temp;
		temp = temp->next_node;
	} 

	return NULL;

} 




 
void push_into_stack(node_t* node) {

	node_stack_t* temp;

	temp = (node_stack_t *)calloc(1, sizeof(node_stack_t));
	temp->node= node;
	temp->next_node=STACK;
	STACK=temp;

} 


 
node_t* pop_from_stack() {

	node_t *temp;
	node_stack_t* stack;

	stack=STACK;
	temp=stack->node;
	STACK=stack->next_node;

	free(stack);

	return temp;

}



//재평가힐 노드의 기준
void make_sort(node_t *old) {

	node_t *direct, *previousNode;
	int i;
	int degree = old->degree+1;

	for(i=0; i<8; i++)	{

		if((direct=old->direct[i])==NULL) 
			continue;
		
		//순서 재정렬로 인한 연결된 노드들의 설정값이 얽힌경우 재설정을 해줍니다.
		//자식 노들들을 위해 스택 공간을 이용합니다.

		if(direct->degree > degree) {
			direct->prev_node = old;
			direct->degree	 = degree;
			direct->value_factor	 = direct->distance+direct->degree;			
			push_into_stack(direct);
		}

	}

	while(STACK) {

		previousNode = pop_from_stack();

		for(i=0; i<8; i++)	{

			if((direct=previousNode->direct[i])==NULL) 
				break;	

			if(direct->degree > previousNode->degree+1) {
				direct->prev_node = previousNode;
				direct->degree	 = previousNode->degree+1;
				direct->value_factor	 = direct->distance+direct->degree;
				push_into_stack(direct);
			}
		}
	}
}


//확장한 새 노드
void insert_node(node_t* present) {
	
	node_t* old = NULL, *temp = NULL;

	if(OPEN == NULL) {
		OPEN = present;
		return;
	} 

	temp=OPEN;
 
	//OpenNode에 있는 노드가 현재 자식 노드보다 평가치가 낮으면
	//OpenNode를 추적해서 현재 자식 노드보다 평가치가 높은 노드를 찾는다.
	

	while(temp && (temp->value_factor < present->value_factor)) {
		old=temp;		
		temp=temp->next_node;
	} 
	
	//낮은 평가치의 OpenNode 중 출발지에 가장 가까운 노드 -> 추가할 자식 노드 -> 높은 평가치의 OpenNode 중 출발지에 가
	//장 먼 노드
	
	if(old) {
		present->next_node = temp;
		old->next_node = present;
	}else {
		present->next_node = temp;
		OPEN = present;
	} 

} 



void extend_child_node(node_t* node, int x, int y, int dest_x, int dest_y, int cur_direct ) {

	node_t* old = NULL, *child = NULL;
	int degree= node->degree+1;

	//확장할 노드가 OpenNode에 존재한다면, 
	if((old=is_open(x, y))) {
	 
		node->direct[ cur_direct ] = old;

		//그리고 노드 재연결 및 설정 . 참고로 노드 방향이 반대로 적용된다는 걸 고려할 것. 
		if(degree<old->degree) {
			old->prev_node = node;
			old->degree = degree;
			old->value_factor = old->distance + old->degree;
		}//if()

	}else if((old=is_closed(x, y))) {//확장할 노드가 CloseNode에 존재한다면,
		
		node->direct[ cur_direct ] = old;

		//어떤 경우에는 기존 CloseNode에 있는 노드의 degree가 더 적을 경우가 발생할 수도 있는데
		//이 때 순서를 다시 설정      
		
		if(degree<old->degree) {
			old->prev_node = node;
			old->degree = degree;
			old->value_factor = old->distance + old->degree;
			make_sort(old);
		}//if()
		//확장할 노드 생성 및 OpenNode 리스트에 추가
	}else {
		if((child =(node_t* )calloc(1, sizeof(node_t))) == NULL)
			return;				 

		child->prev_node=node;
		child->degree = degree;
		child->distance = (x-dest_x)*(x-dest_x)+(y-dest_y)*(y-dest_y);
		child->value_factor = child->distance + child->degree;
		child->x = x;
		child->y = y;

		insert_node(child);

		node->direct[ cur_direct ] = child;
		/*
		for(i=0; i<8; i++) {
			if(node->direct[i]==NULL) {
				node->direct[i]=child;
				break;
			}//if()
		}//for()
		 */
 
	}

}


 
char make_child(node_t* node, int dest_x, int dest_y) {

	int x, y;
	char flag=0;
	char checkis_available_grid[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	x=node->x;
	y=node->y;

	//¿Ãµø ∞°¥…«—¡ˆ ø©∫Œ ∆«¥‹.
	checkis_available_grid[DIRECTION_RIGHTDOWN]=is_available_grid(x, y+1);
	checkis_available_grid[DIRECTION_DOWN]=is_available_grid(x, y+1);
	checkis_available_grid[DIRECTION_LEFTDOWN]=is_available_grid(x-1, y+1);
	checkis_available_grid[DIRECTION_LEFT]=is_available_grid(x-1, y);
	checkis_available_grid[DIRECTION_LEFTUP]=is_available_grid(x-1, y-1);
	checkis_available_grid[DIRECTION_UP]=is_available_grid(x, y-1);
	checkis_available_grid[DIRECTION_RIGHTUP]=is_available_grid(x+1, y-1);
	checkis_available_grid[DIRECTION_RIGHT]=is_available_grid(x+1, y);

	//∞¢ ¿Ãµø ∞°¥…«— ≥ÎµÂø° ¥Î«— ¿⁄Ωƒ ≥ÎµÂ ª˝º∫ 
	if(checkis_available_grid[DIRECTION_LEFT]) {
		extend_child_node(node, x-1, y, dest_x, dest_y,DIRECTION_LEFT);
		flag=1;
	}//if()

	if(checkis_available_grid[DIRECTION_RIGHT]) {
		extend_child_node(node, x+1, y, dest_x, dest_y,DIRECTION_RIGHT);
		flag=1;
	}//if()

	if(checkis_available_grid[DIRECTION_UP]) {
		extend_child_node(node, x, y-1, dest_x, dest_y,DIRECTION_UP);
		flag=1;
	}//if()

	if(checkis_available_grid[DIRECTION_DOWN]) {
		extend_child_node(node, x, y+1, dest_x, dest_y,DIRECTION_DOWN);
		flag=1;
	}//if()

	/*
	if(checkis_available_grid[DIRECTION_RIGHTDOWN] && checkis_available_grid[DIRECTION_RIGHT] && checkis_available_grid[DIRECTION_DOWN]) {
		extend_child_node(node, x+1, y+1, dest_x, dest_y,DIRECTION_RIGHTDOWN);
		flag=1;
	}//if()

	if(checkis_available_grid[DIRECTION_LEFTUP] && checkis_available_grid[DIRECTION_LEFT] && checkis_available_grid[DIRECTION_UP]) {
		extend_child_node(node, x-1, y-1, dest_x, dest_y,DIRECTION_LEFTUP);
		flag=1;
	}//if()

	if(checkis_available_grid[DIRECTION_RIGHTUP] && checkis_available_grid[DIRECTION_RIGHT] && checkis_available_grid[DIRECTION_UP]) {
		extend_child_node(node, x+1, y-1, dest_x, dest_y,DIRECTION_RIGHTUP);
		flag=1;
	}//if()

	if(checkis_available_grid[DIRECTION_LEFTDOWN] && checkis_available_grid[DIRECTION_LEFT] && checkis_available_grid[DIRECTION_DOWN]) {
		extend_child_node(node, x-1, y+1, dest_x, dest_y,DIRECTION_LEFTDOWN);
		flag=1;
	}//if()
	 */
	return flag;

}//char MakeChild(node_t* node, int dest_x, int dest_y)


 
node_t* find_path(int start_x, int start_y, int dest_x, int dest_y) {

	node_t* present, *best=NULL;
	int count=0;//탐색 깊이 값을 카운팅 합니다.  무한 루프에 빠질 가능성을 제한할 용도이죠.

	present = (node_t* )calloc(1, sizeof(node_t));
	present->degree=0;
	present->distance=(dest_x-start_x)*(dest_x-start_x)+(dest_y-start_y)*(dest_y-start_y);
	present->value_factor=present->distance;
	present->x=dest_x;
	present->y=dest_y;

	OPEN=present;

	//탐색 시작합니다. 길 찾기를 실패할 경우에 대비해서 루프문에 제한을 둘 필요가 있습니다.
	while(count< FINDPATH_LIMIT) { 

		//모든 노드에 대한 찾기를 수행했을 경우. 그럴 경우 아마 최적의 길을 찾았겠죠? 아마..
		if(OPEN==NULL)
		{
			//return best;
			return FALSE;
		}

		best = OPEN;     //매 루프문을 돌면서 OpenNode의 후보로부터 탐색을 우선 시도합니다. 
		OPEN = best->next_node;     //그리고 그 다음 노드가 OpenNode의 최상위 후보노드로 지정되며 
		best->next_node = CLOSED;  //지금까지 구축된 최적의 노드를 이번에 탐색할 best노드와 연결함으로써
		//현재까지 탐색된  최적의 길을 유지하게 됩니다. 
		CLOSED=best;   //이 best노드는 이번 루프에서 탐색 시도되므로 close노드로 들어가게 되는거죠.        

		
		
		//길찾기 실패
		if(best==NULL) 
			return NULL;

		//길찾기 성공 
		if(best->x == start_x && best->y == start_y)
		{

			return best;
		}

		//현재 탐색 노드를 중심으로 8방향으로 확장. 		
 		if(make_child(best, start_x, start_y)==0 && count ==0) 
			return NULL;
		count++;
	} 
	return FALSE;
	//return best;
}


M_Boolean setAstar(int startX,int startY,int endX,int endY,int type,int floor)
{
	if(startX == endX && startY == endY)
		return FALSE;
	
	xAstar.startX = startX;
	xAstar.startY = startY;
	xAstar.endX = endX;
	xAstar.endY = endY;
	
	
	
		
	//외각은 자동으로 불가능 처리 해준다 start:-1 max:+2
	for(int x=0;x<xMap.shopPointW+2;x++)
	{
		for(int y=0;y<xMap.shopPointH+2;y++)
		{
			if(x == 0 || y == 0 || x == xMap.shopPointW+1 || y == xMap.shopPointH+1)
				xAstar.mapData[x][y] = TRUE;
			else if(xAstar.startX == x-1 && xAstar.startY == y-1)
				xAstar.mapData[x][y] = FALSE;
			else
				xAstar.mapData[x][y] = xMap.shopData[floor][type][x-1][y-1];
		}			
	}

		//초기화
	init_astar();

	//길찾기
	xAstar.best = find_path(xAstar.startX+1, xAstar.startY+1, xAstar.endX+1, xAstar.endY+1);
	xAstar.totalCnt = 0;
	if(xAstar.best == NULL)
		return FALSE;
	

	while(xAstar.best){
		xAstar.tempX[xAstar.totalCnt] = xAstar.best->x;
		xAstar.tempY[xAstar.totalCnt++] = xAstar.best->y;
		xAstar.best = xAstar.best->prev_node;
	}
	
	
	
	
	//반대로 되있기때문에 재정렬
	
	
	
	
	for(int i=0;i<xAstar.totalCnt;i++)
	{
		xAstar.bestX[i] = xAstar.tempX[i]-1;
		xAstar.bestY[i] = xAstar.tempY[i]-1;
	}		
	return TRUE;
}


