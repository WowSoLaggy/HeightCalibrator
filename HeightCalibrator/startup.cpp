#include "stdafx.h"


#include "SimpleTest.h"


int main()
{
	SimpleTest test;
	std::vector<Post> posts;


	posts.push_back(Post(57, 272, 146, 180));
	posts.push_back(Post(706, 226, 150, 180));
	posts.push_back(Post(476, 180, 136, 180));
	//PostImage testPost(393, 451, 222);
	PostImage testPost(228, 185, 134);
	test.Run("../Images/Street1.png", posts, testPost);


    return 0;
}
