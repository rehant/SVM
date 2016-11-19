#ifndef VEC3D_HPP
#define VEC3D_HPP


class Vec3D
{
    public:
        Vec3D() {x = 0; y = 0; z = 0;}

        /** Constructs Vec2D with X,Y,Z */
        Vec3D(double x, double y, double z);

        /** Default destructor */
        virtual ~Vec3D();

        /** Copy constructor
         *  \param other Object to copy from
         */
        Vec3D(const Vec3D& other);

        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        Vec3D& operator=(const Vec3D& other);

        /** Access x
         * \return The current value of x
         */
        double getX() const { return x; }

        /** Set x
         * \param val New value to set
         */
        void setX(double val) { x = val; }

        /** Access y
         * \return The current value of y
         */
        double getY() const { return y; }

        /** Set y
         * \param val New value to set
         */
        void setY(double val) { y = val; }

        /** Access z
         * \return The current value of z
         */
        double getZ() const { return z; }

        /** Set z
         * \param val New value to set
         */
        void setZ(double val) { z = val; }
    protected:

    private:
        double x; //!< Member variable "x"
        double y; //!< Member variable "y"
        double z; //!< Member variable "z"
        double mag; // Magnitude
};

#endif // VEC3D_HPP
