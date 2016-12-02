#ifndef ROTATIONNODE_HPP
#define ROTATIONNODE_HPP

#include "SceneNode.hpp"


class RotationNode : public SceneNode
{
    public:
        /** Default constructor */
        RotationNode(float xRot, float yRot, float zRot);

        /** Default destructor */
        virtual ~RotationNode();

        /** Access xRot
         * \return The current value of xRot
         */
        float getXRot() { return xRot; }

        /** Set xRot
         * \param val New value to set
         */
        void setXRot(float val) { xRot = val; }

        /** Access yRot
         * \return The current value of yRot
         */
        float getYRot() { return yRot; }

        /** Set yRot
         * \param val New value to set
         */
        void setYRot(float val) { yRot = val; }

        /** Access zRot
         * \return The current value of zRot
         */
        float getZRot() { return zRot; }

        /** Set zRot
         * \param val New value to set
         */
        void setZRot(float val) { zRot = val; }

        int getType() {return type;}

    protected:
        int type = 1;

    private:
        float xRot; // Rotation about x axis
        float yRot; // Rotation about y axis
        float zRot; // Rotation about z axis
};

#endif // ROTATIONNODE_HPP
