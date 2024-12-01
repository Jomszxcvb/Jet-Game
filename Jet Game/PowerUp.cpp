#include "PowerUp.h"
#include <GL/glut.h>

PowerUp::PowerUp(PowerUpType type, float x, float y) : type(type), posX(x), posY(y), speed(2.0f) {}

void PowerUp::update(float deltaTime, float playerX, float playerY) {
    // Move towards the player
    float directionX = playerX - posX;
    float directionY = playerY - posY;
    float length = sqrt(directionX * directionX + directionY * directionY);
    if (length != 0) {
        directionX /= length;
        directionY /= length;
    }
    posX += directionX * speed * deltaTime;
    posY += directionY * speed * deltaTime;
}

bool PowerUp::checkCollision(float playerX, float playerY, float playerSize) const {
    return (std::abs(posX - playerX) < playerSize && std::abs(posY - playerY) < playerSize);
}

PowerUpType PowerUp::getType() const {
    return type;
}

void PowerUp::HomingMissileSprite() const{
	GLfloat outerVertices[] = {
		// left side
		0.0f, 0.7f, 0.0f,
		-0.6f, 0.36f, 0.0f,
		-0.6f, -0.36f, 0.0f,
		0.0f, -0.7f, 0.0f,
		0.6f, -0.36f, 0.0f,
		0.6f, 0.36f, 0.0f
	};
	
	GLubyte outerIndices[] = {0, 1, 2, 3, 4, 5};
	 
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3ub(161, 0, 0);
    glVertexPointer(3, GL_FLOAT, 0, outerVertices);
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, outerIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    
    
    GLfloat innerVertices1[] = {
		// left side
		0.0f, 0.54f, 0.0f,
		-0.45f, 0.25f, 0.0f,
		-0.45f, -0.25f, 0.0f,
		0.0f, -0.54f, 0.0f,
		0.45f, -0.25f, 0.0f,
		0.45f, 0.25f, 0.0f,
	};
	
	GLubyte innerIndices1[] = {0, 1, 2, 3, 4, 5};
	 
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3ub(255, 244, 200);
    glVertexPointer(3, GL_FLOAT, 0, innerVertices1);
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, innerIndices1);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    GLfloat innerVertices2[] = {
		// left side
		0.0f, 0.47f, 0.0f,
		-0.4f, 0.235f, 0.0f,
		-0.4f, -0.235f, 0.0f,
		0.0f, -0.47f, 0.0f,
		0.4f, -0.235f, 0.0f,
		0.4f, 0.235f, 0.0f,
	};
	
	GLubyte innerIndices2[] = {0, 1, 2, 3, 4, 5};
	 
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3ub(255, 255, 255);
    glVertexPointer(3, GL_FLOAT, 0, innerVertices2);
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, innerIndices2);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    GLfloat arrowHeadsVertices[] = {
        // Top arrow
        0.0f, 0.05f, 0.0f,
        -0.1f, 0.23f, 0.0f,
        0.1f, 0.23f, 0.0f,

        // Left arrow
        -0.14f, -0.19f, 0.0f,
        -0.25f, 0.007f, 0.0f,
        -0.035f, 0.007f, 0.0f,

        // Right arrow
        0.14f, -0.19f, 0.0f,
        0.035f, 0.007f, 0.0f, 
        0.25f, 0.007f, 0.0f
    };

    GLubyte arrowHeadsIndices[] = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, arrowHeadsVertices);
	glColor3ub(161, 0, 0);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_BYTE, arrowHeadsIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    GLfloat arrowBodyVertices[] = {
        // Top arrow
        -0.034f, 0.23f, 0.0f,
        -0.034f, 0.57f, 0.0f,
        0.034f, 0.57f, 0.0f,
        0.034f, 0.23f, 0.0f,

        // Left arrow
        -0.175f, -0.12f, 0.0f,
        -0.20f, -0.06f, 0.0f,
        -0.5f, -0.24f, 0.0f,
        -0.466f, -0.3f, 0.0f,

        // Right arrow
        0.175f, -0.12f, 0.0f,
        0.20f, -0.06f, 0.0f,
        0.5f, -0.24f, 0.0f,
        0.466f, -0.3f, 0.0f,
    };


    GLubyte arrowBodyIndices[] = {
        0, 1, 2, 3, 
		4, 5, 6, 7,
		8, 9, 10, 11
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, arrowBodyVertices);
	glColor3ub(161, 0, 0);
    glDrawElements(GL_QUADS, 12, GL_UNSIGNED_BYTE, arrowBodyIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    
}

void PowerUp::GigantificationSprite() const{
	GLfloat outerVertices[] = {

		0.0f, 0.7f, 0.0f,
		-0.6f, 0.36f, 0.0f,
		-0.6f, -0.36f, 0.0f,
		0.0f, -0.7f, 0.0f,
		0.6f, -0.36f, 0.0f,
		0.6f, 0.36f, 0.0f
	};
	
	 GLubyte outerIndices[] = {0, 1, 2, 3, 4, 5};
	 
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3ub(240, 255, 240);
    glVertexPointer(3, GL_FLOAT, 0, outerVertices);
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, outerIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    GLfloat innerVertices[] = {

		0.0f, 0.63f, 0.0f,
		-0.54f, 0.315f, 0.0f,
		-0.54f, -0.315f, 0.0f,
		0.0f, -0.63f, 0.0f,
		0.54f, -0.315f, 0.0f,
		0.54f, 0.315f, 0.0f
	};
	
	 GLubyte innerIndices[] = {0, 1, 2, 3, 4, 5};
	 
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3ub(204, 255, 204);
    glVertexPointer(3, GL_FLOAT, 0, innerVertices);
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, innerIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    GLfloat trianglesVertices[] = {
        // Top arrow
        0.0f, 0.5f, 0.0f,
        -0.4f, 0.06f, 0.0f,
        0.4f, 0.06f, 0.0f,

        // Left arrow
        0.0f, 0.325f, 0.0f,
        -0.3f, -0.1f, 0.0f,
        0.3f, -0.1f, 0.0f,

        // Right arrow
        0.0f, 0.125f, 0.0f,
        -0.25f, -0.28f, 0.0f,
        0.25f, -0.28f, 0.0f
    };


    GLfloat trianglesColors[] = {

        0.0f, 0.3f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,

        0.0f, 0.5f, 0.0f,
        0.0f, 0.7f, 0.0f,
        0.0f, 0.7f, 0.0f,

        0.0f, 0.7f, 0.0f,
        0.0f, 0.9f, 0.0f,
        0.0f, 0.9f, 0.0f
    };

    GLubyte triangleIndices[] = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, trianglesVertices);
    glColorPointer(3, GL_FLOAT, 0, trianglesColors);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_BYTE, triangleIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void PowerUp::getColor(float& r, float& g, float& b) const {
    switch (type) {
    case PowerUpType::HomingMissile:
        r = 1.0f; g = 0.0f; b = 0.0f; // Red color for HomingMissile
        break;
    case PowerUpType::Gigantification:
        r = 0.0f; g = 0.0f; b = 1.0f; // Blue color for Gigantification
        break;
    }
}

void PowerUp::render() const {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    switch (type) {
        case PowerUpType::HomingMissile:
            HomingMissileSprite();
            break;
        case PowerUpType::Gigantification:
            GigantificationSprite();
            break;
    }
    glPopMatrix();
}
