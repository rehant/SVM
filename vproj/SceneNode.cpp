#include "SceneNode.hpp"

SceneNode::SceneNode()
{
}

SceneNode::~SceneNode()
{
	/* Release children */
	for (list<SceneNode*>::iterator i = childList.begin(), end = childList.end(); i != end; ++i)
	{
		delete *i; // Delete this child (Call its destructor)
	}
}

void SceneNode::update()
{
    for (list<SceneNode*>::const_iterator i = childList.begin(), end = childList.end(); i != end; ++i) // Loop through list and update children
    {
        (*i)->update(); // Update child
    }
}

void SceneNode::addChild(SceneNode* pNode)
{
    childList.push_back(pNode);
}
