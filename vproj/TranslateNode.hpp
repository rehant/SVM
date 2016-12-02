#ifndef TRANSLATENODE_HPP
#define TRANSLATENODE_HPP

#include "SceneNode.hpp"


class TranslateNode : public SceneNode
{
    public:
        /** Default constructor */
        TranslateNode(float xTranslate, float yTranslate, float zTranslate);

        /** Default destructor */
        virtual ~TranslateNode();

        /** Access xt
         * \return The current value of xt
         */
        float getX() { return xt; }

        /** Set xt
         * \param val New value to set
         */
        void setX(float val) { xt = val; }

        /** Access yt
         * \return The current value of yt
         */
        float getY() { return yt; }

        /** Set yt
         * \param val New value to set
         */
        void setY(float val) { yt = val; }

        /** Access zt
         * \return The current value of zt
         */
        float getZ() { return zt; }

        /** Set zt
         * \param val New value to set
         */
        void setZ(float val) { zt = val; }

    int getType() {return type;}

    protected:
        int type = 3;

    private:
        float xt; // X Translate
        float yt; // Y Translate
        float zt; // Z Translate
};

#endif // TRANSLATENODE_HPP
