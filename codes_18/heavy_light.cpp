int chainNo[Max];
int pos_in_chain[Max];
int parent_in_chain[Max];
int parent[Max];
int chain_count=0;
int total_in_chain[Max];
int pos_count=0;
vector<int> graph[Max];
int arr[Max];
int subtree_count[Max];
int max_in_subtree[Max];
int height[Max];
vector<vector<pair<int,int> > > vec;
int max_elem,max_count;
void simple_dfs(int i){
	subtree_count[i]=1;
	int max_val=0;
	int ind=-1; 
	for(auto itr:graph[i]){
		height[itr]=1+height[i];
		simple_dfs(itr);
		subtree_count[i]+=subtree_count[itr];
		if(max_val<subtree_count[itr]){
			max_val=subtree_count[itr];
			ind=itr;
		}
	}
	max_in_subtree[i]=ind;
}
void dfs(int i){
	if(pos_count==0)
		parent_in_chain[chain_count]=i;
	chainNo[i]=chain_count;
	pos_in_chain[i]=++pos_count;
	total_in_chain[chain_count]++;
	if(max_in_subtree[i]!=-1){
		dfs(max_in_subtree[i]);
	}
	for(auto itr:graph[i]){
		if(itr!=max_in_subtree[i]){
			chain_count++;
			pos_count=0;
			dfs(itr);
		}
	}
}
int pos;int chain;int val;
void update(int s,int e,int n){
	if(pos>e || pos<s)
		return;
	vec[chain][n]={val,1};
	if(s==e)
		return;
	int mid=(s+e)>>1;
	update(s,mid,2*n);
	update(mid+1,e,2*n+1);
	if(vec[chain][2*n].x<vec[chain][2*n+1].x)
		vec[chain][n]=vec[chain][2*n+1];
	else if(vec[chain][2*n].x>vec[chain][2*n+1].x)
		vec[chain][n]=vec[chain][2*n];
	else{
		vec[chain][n]={vec[chain][2*n].x,vec[chain][2*n].y+vec[chain][2*n+1].y};
	}
}
int qs;int qe;
void query_tree(int s,int e,int n){
	if(s>qe || qs>e)
		return;
	if(s>=qs && e<=qe){
		if(vec[chain][n].x>max_elem){
			max_elem=vec[chain][n].x;
			max_count=vec[chain][n].y;
		}
		else if(vec[chain][n].x==max_elem){
			max_count+=vec[chain][n].y;
		}
		return;
	}
	if(vec[chain][n].x <max_elem)
		return;
	int mid=(s+e)>>1;
	query_tree(s,mid,2*n);
	query_tree(mid+1,e,2*n+1);
}
void query(int i){
	if(i==-1)
		return;
	qs=1;qe=pos_in_chain[i];chain=chainNo[i];
	query_tree(1,total_in_chain[chainNo[i]],1);
	i=parent[parent_in_chain[chainNo[i]]];
	query(i);
}