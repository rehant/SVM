#include "TranslateNode.hpp"

TranslateNode::TranslateNode(int xTranslate, int yTranslate, int zTranslate)
{
    /* Save translates */
    xt = xTranslate;
    yt = yTranslate;
    zt = zTranslate;
}

TranslateNode::~TranslateNode()
{
}
