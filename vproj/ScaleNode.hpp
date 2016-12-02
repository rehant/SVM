#ifndef SCALENODE_HPP
#define SCALENODE_HPP

#include "SceneNode.hpp"

class ScaleNode : public SceneNode
{
    public:
        /** Default constructor */
        ScaleNode(float xScal, float yScal, float zScal);

        /** Default destructor */
        virtual ~ScaleNode();

        /** Access xScale
         * \return The current value of xRot
         */
        float getXScale() { return xScale; }

        /** Set xScale
         * \param val New value to set
         */
        void setXScale(float val) { xScale = val; }

        /** Access yScale
         * \return The current value of yRot
         */
        float getYScale() { return yScale; }

        /** Set yScale
         * \param val New value to set
         */
        void setYScale(float val) { yScale = val; }

        /** Access zScale
         * \return The current value of zRot
         */
        float getZScale() { return zScale; }

        /** Set zScale
         * \param val New value to set
         */
        void setZScale(float val) { zScale = val; }

        int getType() {return type;}

    protected:
        int type = 2;

    private:
        float xScale; // X scale
        float yScale; // Y scale
        float zScale; // Z scale
};

#endif // SCALENODE_HPP
