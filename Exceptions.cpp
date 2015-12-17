#include "Exceptions.h"

std::ostream & Gaming::operator<<(std::ostream & os, const GamingException & ex)
{
	return os;
}

void Gaming::GamingException::setName(std::string name)
{
	__name = name;
}

Gaming::DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height)
{
	__exp_width = expWidth;
	__exp_height = expHeight;
	__width = width;
	__height = height;
}

unsigned Gaming::DimensionEx::getExpWidth() const
{
	return __exp_width;
}

unsigned Gaming::DimensionEx::getExpHeight() const
{
	return __exp_height;
}

unsigned Gaming::DimensionEx::getWidth() const
{
	return __width;
}

unsigned Gaming::DimensionEx::getHeight() const
{
	return __height;
}

void Gaming::InsufficientDimensionsEx::__print_args(std::ostream & os) const
{
	os << "Execption Generated: InsufficientDimensionsEx" << std::endl;
}

Gaming::InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height) : DimensionEx(minWidth, minHeight, width, height)
{
	__name = "InsufficientDimensionsEx";
}

void Gaming::OutOfBoundsEx::__print_args(std::ostream & os) const
{
	os <<	"Exception Generated : OutOfBoundsEx" << std::endl;
}

Gaming::OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) : DimensionEx(maxWidth,maxHeight,width,height)
{
	setName("OutOfBoundsEx");
}
