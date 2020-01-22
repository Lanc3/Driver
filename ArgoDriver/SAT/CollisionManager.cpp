#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
	
}

void CollisionManager::checkConcave(std::vector<Collider*>* colliders, Collider* col)
{
	float zCrossProduct = 0;
	float zCrossProductLastNum = 0;
	int indexWithIndent;

	int colSize = col->getSize();
	glm::vec2* colPoints = col->getPoints();

	bool convcave = false;
	for (int i = 0; i < colSize; i++)
	{
		glm::vec2 ab1, ab2;
		if (i == colSize - 1) //last index
		{
			indexWithIndent = 0;
			ab1 = colPoints[0] - colPoints[i];
			ab2 = colPoints[1] - colPoints[0];
		}
		else if (i == colSize - 2)//second last index
		{
			indexWithIndent = i + 1;
			ab1 = colPoints[i + 1] - colPoints[i];
			ab2 = colPoints[0] - colPoints[i + 1];
		}
		else
		{
			indexWithIndent = i + 1;
			ab1 = colPoints[i + 1] - colPoints[i];
			ab2 = colPoints[i + 2] - colPoints[i + 1];

		}

		zCrossProduct = ab1.x*ab2.y - ab1.y*ab2.x;


		if (zCrossProduct > 0 && zCrossProductLastNum < 0) //concave shape, positive, negative
		{
			convcave = true;
			break;
		}
		else if (zCrossProduct < 0 && zCrossProductLastNum > 0) //concave shape, negative, position
		{
			convcave = true;
			break;
		}
		zCrossProductLastNum = zCrossProduct;
	}
	if (convcave)
	{
		glm::vec2 pointA;
		glm::vec2 axis;

		int i = indexWithIndent;
		if (indexWithIndent == 0) // first index
		{
			pointA = colPoints[colSize - 1];
			axis = colPoints[1] - pointA;
		}
		else if (indexWithIndent == colSize - 1) //last index
		{
			pointA = colPoints[indexWithIndent - 1];
			axis = colPoints[0] - pointA;
		}
		else
		{
			pointA = colPoints[indexWithIndent - 1];
			axis = colPoints[indexWithIndent + 1] - pointA;
		}
		axis = glm::normalize(axis);

		float closestPoint = 999999999; //large number to check for less then for closest point
		int closestIndex;
		for (int i = 0; i < colSize; i++)
		{
			glm::vec2 vectorAC = colPoints[i] - pointA;
			if (i != indexWithIndent)
			{
				if (isLeft(axis, vectorAC))
				{
					float distance = glm::distance(colPoints[indexWithIndent], colPoints[i]);
					if (distance < closestPoint)
					{
						closestPoint = distance;
						closestIndex = i;
					}
				}
			}

		}
		std::vector<int> usedIndex; //index that is use for first polygon.
		std::vector<SDL_Point> polygonA; //polygon one
		std::vector<SDL_Point> polygonB; //polygon two
		//check if it is revise and swap
		if (closestIndex < indexWithIndent)
		{
			int temp = indexWithIndent;
			indexWithIndent = closestIndex;
			closestIndex = temp;
		}
		//make first polygon
		for (int i = indexWithIndent; i < closestIndex + 1; i++)
		{
			polygonB.push_back(SDL_Point{ (int)(colPoints[i].x), (int)(colPoints[i].y) });
			if (i != indexWithIndent && i != closestIndex)
			{
				usedIndex.push_back(i);
			}
		}
		//make second polygon
		for (int i = 0; i < colSize; i++)
		{
			if (!usedIndex.empty())
			{
				bool used = false;
				for (int j = 0; j < usedIndex.size(); j++)
				{
					if (i == usedIndex[j])
					{
						used = true;

					}
				}
				if (!used)
				{
					polygonA.push_back(SDL_Point{ (int)(colPoints[i].x),  (int)(colPoints[i].y) });
				}
			}
			else
			{
				polygonA.push_back(SDL_Point{ (int)(colPoints[i].x),  (int)(colPoints[i].y) });
			}
		}

		//converting to points 
		SDL_Point* polyAPoints = new SDL_Point[polygonA.size()];
		int polyASize = polygonA.size();
		for (int i = 0; i < polygonA.size(); i++)
		{
			polyAPoints[i] = polygonA[i];
		}

		SDL_Point* polyBPoints = new SDL_Point[polygonA.size()];
		int polyBSize = polygonB.size();
		for (int i = 0; i < polygonB.size(); i++)
		{
			polyBPoints[i] = polygonB[i];
		}

		//pushing new polygon to test for concave
		checkConcave(colliders, new Polygon(polyAPoints, polyASize));
		checkConcave(colliders, new Polygon(polyBPoints, polyBSize));

		delete[]polyAPoints;
		polyAPoints = nullptr;
		delete[]polyBPoints;
		polyBPoints = nullptr;
	}
	else
	{
		colliders->push_back(col);
	}
}

bool CollisionManager::SAT(Collider& col1, Collider& col2)
{
	std::vector<Collider*> collidersA = std::vector<Collider*>();
	std::vector<Collider*> collidersB = std::vector<Collider*>();
	checkConcave(&collidersA, &col1);
	checkConcave(&collidersB, &col2);

	for (int i = 0; i < collidersA.size(); i++)
	{
		for (int j = 0; j < collidersB.size(); j++)
		{
			/*if (SATForConvex(*collidersA[i], *collidersB[j]))
			{
				return true;
			}*/
		}
	}
	return false;
}
CollisionData  CollisionManager::SATForConvex(Polygon& colA, Polygon& colB, glm::vec2 velocity)
{
	CollisionData collisionData;
	collisionData.isColliding = true;
	collisionData.willCollide = true;
	int sizeA = colA.getSize();
	int sizeB = colB.getSize();
	glm::vec2* pointsA = colA.getPoints();
	glm::vec2* pointsB = colB.getPoints();
	glm::vec2 translationAxis = glm::vec2(0, 0);
	glm::vec2 MinimumTranslationVector = glm::vec2(0, 0);
	float minIntervalDistance = numeric_limits<float>::infinity();
	float minA, maxA, minB, maxB;
	// get first separating axis

	vector<glm::vec2> separatingAxisA;
	for (int i = 0; i < sizeA; i++)
	{
		glm::vec2 normal;
		glm::vec2 ab;
		if (i != sizeA - 1) {
			ab = pointsA[i + 1] - pointsA[i];
			normal = glm::vec2(-ab.y, ab.x);
		}
		else {
			ab = pointsA[0] - pointsA[sizeA - 1];
			normal = glm::vec2(-ab.y, ab.x);
		}
		separatingAxisA.push_back(normal);
	}
	// get second separating axis

	vector<glm::vec2> separatingAxisB ;
	for (int i = 0; i < sizeB; i++)
	{
		glm::vec2 normal;
		glm::vec2 ab;
		if (i != sizeB - 1) {
			ab = pointsB[i + 1] - pointsB[i];
			normal = glm::vec2(-ab.y, ab.x);
		}
		else {

			ab = pointsB[0] - pointsB[sizeB - 1];
			normal = glm::vec2(-ab.y, ab.x);
		}
		separatingAxisB.push_back(normal);
	}
	for (unsigned i = 0; i < sizeB; i++) {
		glm::vec2 axis = separatingAxisB[i];
		axis = glm::normalize(axis);
		ProjectPolygon(axis, pointsA, sizeA, minA, maxA);
		ProjectPolygon(axis, pointsB, sizeB, minB, maxB);


		if (IntervalDistance(minA, maxA, minB, maxB) > 0)
		{
			collisionData.isColliding = false;
		}

		float velocityProjection = glm::dot(axis, velocity);

		// Get the projection of polygon A during the movement
		if (velocityProjection < 0) {
			minA += velocityProjection;
		}
		else {
			maxA += velocityProjection;
		}
		//same test again
		// Do the same test as above for the new projection
		float intervalDistance = IntervalDistance(minA, maxA, minB, maxB);
		if (IntervalDistance(minA, maxA, minB, maxB) > 0)
		{
			collisionData.willCollide = false;
		}

		// If the polygons are not intersecting and won't intersect, exit the loop
		//if (!collisionData.isColliding && !collisionData.willCollide) break;


		intervalDistance = abs(intervalDistance);
		if (intervalDistance < minIntervalDistance) {
			minIntervalDistance = intervalDistance;
			translationAxis = axis;

			glm::vec2 d = colA.GetCenter() - colB.GetCenter();
			if (glm::dot(d, translationAxis) < 0)
			{
				translationAxis.x = -translationAxis.x;
				translationAxis.y = -translationAxis.y;
			}
		}
	}

	// The minimum translation vector
	// can be used to push the polygons appart.
	if (collisionData.willCollide)
	{
		collisionData.MTV = translationAxis * minIntervalDistance;
	}
	return collisionData;
}
float CollisionManager::IntervalDistance(float minA, float maxA, float minB, float maxB) {
	if (minA < minB) {
		return minB - maxA;
	}
	else {
		return minA - maxB;
	}
}
//Pvector axis = separatingAxisB[i];
//axis.normalize();
//maxA = pointsA[0].dotProduct(axis);
//minA = maxA;
//for (unsigned j = 0; j < sizeA; j++) {
//	float currentLenghtProj = pointsA[j].dotProduct(axis);
//	if (minA > currentLenghtProj) {
//		minA = currentLenghtProj;
//	}
//	if (currentLenghtProj > maxA) {
//		maxA = currentLenghtProj;
//	}
//}
void CollisionManager::ProjectPolygon(glm::vec2 axis, glm::vec2 * points, int size, float & min, float & max) {
	// To project a point on an axis use the dot product
	float dotProduct = glm::dot(glm::normalize(axis), points[0]);
	min = dotProduct;
	max = dotProduct;
	for (int i = 0; i < size; i++) {
		dotProduct = glm::dot(points[i], axis);
		if (dotProduct < min) {
			min = dotProduct;
		}
		else {
			if (dotProduct > max) {
				max = dotProduct;
			}
		}
	}
}


bool CollisionManager::PixelCollision(PixelCollider& col1, PixelCollider& col2)
{
	std::vector<RectFloat*> colliders1 = col1.getColliders();
	std::vector<RectFloat*> colliders2 = col2.getColliders();
	int count1 = colliders1.size();
	int count2 = colliders2.size();

	for (int i = 0; i < count1; i++)
	{
		for (int j = 0; j < count2; j++)
		{
			if (checkRect(colliders1[i], colliders2[j]))
			{
				return true;
			}
		}
	}
	return false;
}


bool CollisionManager::checkRect(RectFloat* rect1, RectFloat* rect2)
{
	//Calculate the sides of rect A
	float leftA = rect1->x;
	float rightA = rect1->x + rect1->w;
	float topA = rect1->y;
	float bottomA = rect1->y + rect1->h;

	//Calculate the sides of rect B
	float leftB = rect2->x;
	float rightB = rect2->x + rect2->w;
	float topB = rect2->y;
	float bottomB = rect2->y + rect2->h;

	if (bottomA < topB)
	{
		return false;
	}

	if (topA > bottomB)
	{
		return false;
	}

	if (rightA < leftB)
	{
		return false;
	}

	if (leftA > rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

bool CollisionManager::isLeft(glm::vec2 axis, glm::vec2 point) {
	return (axis.x*point.y - axis.y*point.x) > 0;
}