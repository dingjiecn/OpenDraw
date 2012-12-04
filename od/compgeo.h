 /* -------------------------------------------------------------------------
//	�ļ���		��	compgeo.h
//	������		��	dj
//	����ʱ��	��	2008-1-28
//	��������	��	computational geometry algorithm
//
// -----------------------------------------------------------------------*/
#ifndef __COMPGEO_H__
#define __COMPGEO_H__

#define PI 3.1415926535897f
#define ZERO 1E-5
#define FABS(v) ((v)>0?(v):(-v))

// -------------------------------------------------------------------------
// ���ض�����o�㣬��ʼ��Ϊos����ֹ��Ϊoe�ļн�
// (��λ������)  
// -------------------------------------------------------------------------
template<typename T>
inline float GetAngle(const T& o, const T& s, const T& e) 
{ 
	float cosfi, norm; 
	float dsx = s.x - o.x; 
	float dsy = s.y - o.y; 
	float dex = e.x - o.x; 
	float dey = e.y - o.y; 
	
	cosfi = dsx * dex + dsy * dey; 
	norm = (dsx * dsx + dsy * dsy) * (dex * dex + dey * dey); 
	cosfi /= sqrt(norm); 
	
	if (cosfi >=  1.0 ) return 0; 
	if (cosfi <= -1.0 ) return PI; 
	
	return acos(cosfi); 
}
// -------------------------------------------------------------------------
// �������  
// -------------------------------------------------------------------------
template<typename T>
inline int Dist(const T& pt1, const T& pt2)
{
	return(sqrt((pt1.x-pt2.x)*(pt1.x-pt2.x)+(pt1.y-pt2.y)*(pt1.y-pt2.y)));
}

// -------------------------------------------------------------------------
// ����point��center��תangle�Ƕ��Ժ�ĵ㣬��λ(�Ƕ�)
// -------------------------------------------------------------------------
template<typename T>
inline T RotatePoint(const T& point, const T& center, float angle)
{
	if (FABS(angle)<=ZERO)
		return point;
	CPoint _point;
	CPoint delta = point - center;
	float theta = angle/180*PI;
	_point.x = delta.x*cos(theta)-delta.y*sin(theta)+0.5f;
	_point.y = delta.x*sin(theta)+delta.y*cos(theta)+0.5f;
	_point += center;
	return _point;
}
// -------------------------------------------------------------------------
// �����߶ε����򣬵��������
// -------------------------------------------------------------------------
inline void GetLineRect(POINT points[4], const CPoint& ptStart, 
						const CPoint& ptEnd, POINT penWidth, int nInflate)
{
	int k = (ptStart.x - ptEnd.x)*(ptStart.y - ptEnd.y);
	int x = (penWidth.x + nInflate) / 2;
	int y = (penWidth.y + nInflate) / 2;
	points[0].x = ptStart.x - x;
	points[1].x = ptStart.x + x;
	points[2].x = ptEnd.x + x;
	points[3].x = ptEnd.x - x;
	if (k > 0)
	{
		points[0].y = ptStart.y + y;
		points[1].y = ptStart.y - y;
		points[2].y = ptEnd.y - y;
		points[3].y = ptEnd.y + y;
	}
	else
	{
		points[0].y = ptStart.y - y;
		points[1].y = ptStart.y + y;
		points[2].y = ptEnd.y + y;
		points[3].y = ptEnd.y - y;
	}
}
















#endif //__COMPGEO_H__