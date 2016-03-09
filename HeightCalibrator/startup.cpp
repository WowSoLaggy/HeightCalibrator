#include "stdafx.h"


#include "SimpleTest.h"


int main()
{
	SimpleTest test;
	std::vector<Post> posts;


	//posts.push_back(Post(57, 272, 146, 180));
	//posts.push_back(Post(706, 226, 150, 180));
	//posts.push_back(Post(476, 180, 136, 180));
	//PostImage testPost(393, 451, 222);
	//PostImage testPost(228, 185, 134);
	//test.Run("../Images/Street1.png", posts, testPost);

	/*posts.push_back(Post(192, 561, 399, 190));
	posts.push_back(Post(416, 314, 237, 190));
	posts.push_back(Post(883, 399, 298, 190));*/

	posts.push_back(Post(991, 656, 561, 100));
	posts.push_back(Post(352, 701, 598, 100));
	posts.push_back(Post(715, 277, 241, 100));
	posts.push_back(Post(521, 309, 267, 100));

	//PostImage testPost(614, 520, 392);
	PostImage testPost(193, 561, 401);
	//PostImage testPost(415, 314, 237);
	test.Run("../Images/airportTest.jpg", posts, testPost);


    return 0;
}
