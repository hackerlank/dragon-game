/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/10/04
 **********************************************************************/


#include <com/dragon3d/util/math/Quaternion.h>

#include <dragon/lang/Math.h>
#include <com/dragon3d/util/math/Mathf.h>

Import dragon::lang;
Import com::dragon3d::util::math;

const Type* Quaternion::TYPE = TypeOf<Quaternion>();

const Quaternion Quaternion::IDENTITY = Quaternion(0, 0, 0, 1);

Quaternion Quaternion::euler(float x, float y, float z ) {
    float heading = y * Mathf::PI / 180; // mapping heading to y axis
    float pitch = x * Mathf::PI / 180; // mapping pitch to x axis
    float bank = z * Mathf::PI / 180; // mapping bank to z axis

    float angle = pitch * 0.5;
    float sp = Mathf::sin(angle);
    float cp = Mathf::cos(angle);
    
    angle = bank * 0.5;
    float sb = Mathf::sin(angle);
    float cb = Mathf::cos(angle);

    angle = heading * 0.5;
    float sh = Mathf::sin(angle);
    float ch = Mathf::cos(angle);

    float ww =  ch*cp*cb + sh*sp*sb;
    float xx =  ch*sp*cb + sh*cp*sb;
    float yy = -ch*sp*sb + sh*cp*cb;
    float zz = -sh*sp*cb + ch*cp*sb;
   
    return Quaternion(xx, yy, zz, ww).normalize();
}

Quaternion Quaternion::euler(const Vector3& e) {
    return euler(e.x, e.y, e.z);
}

Quaternion Quaternion::angleAxis(float angle, const Vector3& axis) {
    Vector3 normalizeAxis = axis.normalize();

    if (normalizeAxis == Vector3::ZERO) {
        return Quaternion::IDENTITY;
    }

    float halfAngle = 0.5 * angle;
    float _sin = Math::sin(halfAngle);

    float w = Math::cos(halfAngle);
    float x = _sin * normalizeAxis.x;
    float y = _sin * normalizeAxis.y;
    float z = _sin * normalizeAxis.z;

    return Quaternion(x, y, z, w);
}

Quaternion Quaternion::angleAxis(float angle, float x, float y, float z) {
    return angleAxis(angle, Vector3(x, y, z));
}

// -------------------------------------------------------
// 
Quaternion::Quaternion(void) {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->w = 0.0f;
}

Quaternion::Quaternion(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 0.0f;
}

Quaternion::Quaternion(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}



bool Quaternion::operator==(const Quaternion& a) const {
    return x==a.x && y==a.y && z==a.z && w==a.w;
}

bool Quaternion::operator!=(const Quaternion& a) const {
    return x!=a.x || y!=a.y || z!=a.z || w!=a.w;
}

// -------------------------------------------

float Quaternion::magnitudeSquared() const {
    return w * w + x * x + y * y + z * z;
}

float Quaternion::magnitude() const {
    float magnitudeSQ = magnitudeSquared();

    if (magnitudeSQ == 1.0) {
        return 1.0;
    }

    return Math::sqrt(magnitudeSQ);
}

Quaternion Quaternion::normalize() const {
    float n = 1.0 / magnitude();

    float x = this->x * n;
    float y = this->y * n;
    float z = this->z * n;
    float w = this->w * n;

    return Quaternion(x, y, z, w);  
}

Vector3 Quaternion::getEulerAngles() const {
    Vector3 result;

    float sqw = w * w;
    float sqx = x * x;
    float sqy = y * y;
    float sqz = z * z;

    float unit = sqx + sqy + sqz + sqw; // if normalized is one, otherwise

    // is correction factor
    float test = x * y + z * w;

    if (test > 0.499 * unit) { // singularity at north pole
        result.x = 2 * Math::atan2(x, w);
        result.y = Mathf::PI / 2;
        result.z = 0;
    } else if (test < -0.499 * unit) { // singularity at south pole
        result.x = -2 * Math::atan2(x, w);
        result.y = - Mathf::PI / 2;
        result.z = 0;
    } else {
        result.x = Math::atan2(2 * y * w - 2 * x * z, sqx - sqy - sqz + sqw);
        result.y = Math::asin(2 * test / unit);
        result.z = Math::atan2(2 * x * w - 2 * y * z, -sqx + sqy - sqz + sqw);
    }

    return result;
}

void Quaternion::set(float new_x, float new_y, float new_z, float new_w) {
    this->x = new_x;
    this->y = new_y;
    this->z = new_z;
}

void Quaternion::setFromToRotation(const Vector3& fromDirection, const Vector3& toDirection) {
    throw "not implements!";
}

void Quaternion::setLookRotation(const Vector3& view) {
    throw "not implements!";
}

void Quaternion::setLookRotation(const Vector3& view, const Vector3& up) {
    throw "not implements!";
}

void Quaternion::toAngleAxis(float& angle, Vector3& axis) const {
    float thetaOver2 = Mathf::safeAcos(w);
    angle = thetaOver2 * 2.0f;

    float sinThetaOver2Sq = 1.0f - w*w;

    // Protect against numerical imprecision
    if (sinThetaOver2Sq <= 0.0f) {
        // Identity quaternion, or numerical imprecision.  Just
        // return any valid vector, since it doesn't matter
        axis = Vector3(1.0f, 0.0f, 0.0f);
        return;
    }

    // Compute 1 / sin(theta/2)
    float oneOverSinThetaOver2 = 1.0f / Mathf::sqrt(sinThetaOver2Sq);

    // Return axis of rotation
    axis = Vector3(
        x * oneOverSinThetaOver2,
        y * oneOverSinThetaOver2,
        z * oneOverSinThetaOver2
    ); 
}

const Array<Vector3> Quaternion::toAxes() const {
    float norm = magnitudeSquared();
    float s = norm == 1.0 ? 2.0 : norm > 0.0 ? 2.0 / norm : 0;

    // compute xs/ys/zs first to save 6 multiplications, since xs/ys/zs
    // will be used 2-4 times each.
    float xs = this->x * s;
    float ys = this->y * s;
    float zs = this->z * s;
    float xx = this->x * xs;
    float xy = this->x * ys;
    float xz = this->x * zs;
    float xw = this->w * xs;
    float yy = this->y * ys;
    float yz = this->y * zs;
    float yw = this->w * ys;
    float zz = this->z * zs;
    float zw = this->w * zs;

    // using s=2/norm (instead of 1/norm) saves 9 multiplications by 2 here
    Array<Vector3> axes(3);

    axes[0].setX(1.0 - (yy + zz));
    axes[0].setY(xy - zw);
    axes[0].setZ(xz + yw);

    axes[1].setX(xy + zw);
    axes[1].setY(1.0 - (xx + zz));
    axes[1].setZ(yz - xw);

    axes[2].setX(xz - yw);
    axes[2].setY(yz + xw);
    axes[2].setZ(1.0 - (xx + yy));

    return axes;
}

Quaternion Quaternion::conjugate() {
    Quaternion result;
    
    result.w = w;

    // Opposite axis of rotation
    result.x = -x;
    result.y = -y;
    result.z = -z;

    return result;
}

Quaternion Quaternion::add(const Quaternion& q) const {
    return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
}

Quaternion Quaternion::subtract(const Quaternion& q) const {
    return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
}

Quaternion Quaternion::multiply(float scalar) const {
    return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
}

Quaternion Quaternion::multiply(const Quaternion& a) const {
    Quaternion result;

    result.w = w*a.w - x*a.x - y*a.y - z*a.z;
    result.x = w*a.x + x*a.w + z*a.y - y*a.z;
    result.y = w*a.y + y*a.w + x*a.z - z*a.x;
    result.z = w*a.z + z*a.w + y*a.x - x*a.y;

    return result;
}

Quaternion Quaternion::invert() {
    Quaternion store = this->conjugate();
    float magnitudeSQ = magnitudeSquared();

    if (Math::abs(1.0 - magnitudeSQ) <= Mathf::EPSILON) {
        return store;
    } else {
        return store.multiply(1.0 / magnitudeSQ);
    }
}

const float* Quaternion::getData() const {
    return (float*)(&this->x);
}

const Array<float> Quaternion::toFloatArray() const {
    return Array<float>(getData(), 4, false);
}
