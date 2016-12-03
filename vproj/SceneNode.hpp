#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <list>

using namespace std;

class SceneNode
{
    public:
        /** Default constructor */
        SceneNode();

        /** Default destructor */
        virtual ~SceneNode();

        virtual void update();

        void addChild(SceneNode* pNode);

        /** Access childList
         * \return The current value of childList
         */
        list<SceneNode*> getChildList() { return childList; }

        /** Set childList
         * \param val New value to set
         */
        void setChildList(list<SceneNode*> val) { childList = val; }

        int getType() {return type;}

    protected:
        list<SceneNode*> childList; // Child list
        const int type = 0; // Node type. Used to determine how to handle it.

    private:
};

#endif // SCENENODE_HPP
