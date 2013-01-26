/**
 * Lattice Multiplication Algorithm
 * File: lattice_multiplication.hxx
 * Author: iJab(Zhan Caibao) zhancaibaoATgmail.com
 * Date: 2013/01/25
 *
 */

#ifndef __LATTICE_MULTIPLICATION__
#define __LATTICE_MULTIPLICATION__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <limits>

using namespace std;

template <typename TL, typename TR>
class LatticeMultiplication
{
public:
	LatticeMultiplication(TL left = 28, TR right = 28);

	string run();


private:
	/////////////////////////////////////////////////////////////
	// calculation functions
	vector<vector<pair<int, int>>> cal_rect();
	string		sum_up_diagonally(const vector<vector<pair<int, int>>> &rect_v);
	void		print_result(const vector<vector<pair<int, int>>> &rect_v, const string &rv_str);

	
	/////////////////////////////////////////////////////////////
	// Helper functions
	void		check_sign(TL left, TR right);
	void		ensure_string(TL left, TR right);
	vector<int> itov(int n);
	template <typename T> string 		to_string(T _v);
	string 		ltrim(const string &_s, const string &delimiters = " \t\r\n\0\a\b\f\v");
	string 		rtrim(const string &_s, const string &delimiters = " \t\r\n\0\a\b\f\v");
	string 		trim(const string &_s, const string &delimiters = " \t\r\n\0\a\b\f\v");


private:
	string 		lo, ro;
	int 		lo_size, ro_size;
	int 		op_sign;
	int   		length_decimal;
	TL			ori_lo;
	TR			ori_ro;
};

///////////////////////////////////////////////////////////////////////////////
// Class LatticeMultiplication implementation

/**
 * Constructor
 * @param left T, right T
 * @return void
 */
template <typename TL, typename TR> 
LatticeMultiplication<TL, TR>::LatticeMultiplication(TL left/* = 28*/, TR right/* = 28*/)
 											: lo_size(0), ro_size(0) 
 											, op_sign(1), length_decimal(0)
											, ori_lo(left), ori_ro(right)
{
	// While we get the int, float or double inputs, we convert them to string for 
	// multiplication and store the length of decimal
	this->ensure_string(left, right);

	// Store the sign and use it later. We only time operands as positive numbers 
	// while calculating and at last we apply the sign
	this->check_sign(left, right);
}

/**
 * Run the lattice multiplication algorithm
 * @method run
 * @param void
 * @return string Result of Lattice Multiplicaiton
 */
template <typename TL, typename TR> 
string LatticeMultiplication<TL, TR>::run()
{
	vector<vector<pair<int, int>>> rect_v;
	string rv_str;

	// Calculate using rectangle
	rect_v = this->cal_rect();

	// sum up diagonally
	rv_str = this->sum_up_diagonally(rect_v);

	// Print result including rectangle
	this->print_result(rect_v, rv_str);

	return rv_str;
}

/**
 * Calculate with digits arrays and store the result to a two-dimnsion array
 * I use a pair<int, int> to store the high and low position result
 * @method cal_rect
 * @param void
 * @return vector<vector<pair<int, int>>>
 *
 */
template <typename TL, typename TR> 
vector<vector<pair<int, int>>> LatticeMultiplication<TL, TR>::cal_rect()
{
	// two-dimnsion array to store results of multiplication by digit
	// array to store the diagonally sum up result
	vector<vector<pair<int, int>>> rect_v;

	// mulitplifying by digits
	for(int i = 0; i < this->ro_size; i++)
	{
		vector<pair<int, int>> _r;
		for(int j = 0; j < this->lo_size; j++)
		{
			int tmp_mult = (this->lo[j]-'0') * (this->ro[i]-'0');
			pair<int, int> _p_mult(tmp_mult/10, tmp_mult%10);
			_r.push_back(_p_mult);
		}
		rect_v.push_back(_r);
	}

	return rect_v;
}

/**
 * Sum up diagonally to get the result of times
 * @method sum_up_diagonally
 * @param rect_v const vector<vector<pair<int, int>>> &
 * @return string
 *
 */
template <typename TL, typename TR> 
string LatticeMultiplication<TL, TR>::sum_up_diagonally(const vector<vector<pair<int, int>>> &rect_v)
{
	vector<int> result_v;
	// sum up diagonally
	int carry = 0;
	for(int ix = 0; ix < (this->lo_size+this->ro_size); ix++)
	{
		int sum = carry;

		if(ix < this->lo_size) // go through column
		{
			// The diagonal index number can't be larger than the row number 
			int col_loop_ubound = ix > this->ro_size-1 ? this->ro_size-1: ix;
			for(int row_ix = 0; row_ix <= col_loop_ubound; row_ix++ )
			{
				// sum up bottom right: low order digit
				sum += rect_v[this->ro_size-1-row_ix][this->lo_size-1-ix+row_ix].second;
				// sum up left top
				if(ix > row_ix)
				{
					sum += rect_v[this->ro_size-1-row_ix][this->lo_size-1-ix+row_ix+1].first;			
				}
			}
		}
		else				// ix>=this->lo_size - column count of rect, go through row
		{
			for(int row_ix = 0; row_ix <= (this->ro_size-1-(ix-this->lo_size)); row_ix++)
			{
				// sum up bottom right
				if((this->ro_size-1-ix+this->lo_size-row_ix-1) >= 0 &&
					this->ro_size-1-ix-row_ix-1 < 0)
				{
					sum += rect_v[row_ix][this->ro_size-1-ix+this->lo_size-row_ix-1].second;
				}
				// sum up left top
				if(this->ro_size-1-ix+this->lo_size-row_ix < this->lo_size)
				{
					sum += rect_v[row_ix][this->ro_size-1-ix+this->lo_size-row_ix].first;					
				}
			}
		}
		// Store result to array from low to high
		result_v.push_back(sum%10);
		carry = sum/10;
	}

	string rv_str("");
	
	// Convert result to string and apply float point if needed
	int rv_size = (int)result_v.size();
	for(int i = rv_size-1; i >= 0; i--)
	{
		ostringstream ss;
		ss << result_v[i];
		
		rv_str.append(ss.str());
	}
	
	// Add float point if needed
	if(this->length_decimal > 0)
	{
		rv_str.insert(rv_str.size()-this->length_decimal, ".");
	}
		
	// Trim all zeros
	rv_str = this->trim(rv_str, "0");
	
	// Append 0 to float point
	if(rv_str[0] == '.')
	{
		rv_str = "0" + rv_str;
	}

	// Apply sign to the result
	if(this->op_sign < 0)
	{
		rv_str = ("-") + rv_str;
	}
	return rv_str;
}

/**
 * Print the rectangle and the result of multiplication
 * @method print_result
 * @param rect_v const vector<vector<pair<int, int>>> &, rv_str const string&
 * @return void
 *
 */
template <typename TL, typename TR> 
void LatticeMultiplication<TL, TR>::print_result(const vector<vector<pair<int, int>>> &rect_v, const string &rv_str)
{
	// print the array
	vector<vector<pair<int, int>>>::const_iterator rit;
	vector<pair<int, int>> _row_v;
	vector<pair<int, int>>::const_iterator cit;
	for(rit = rect_v.begin(); rit != rect_v.end(); rit++)
	{
		_row_v = *rit;
		for(cit = _row_v.begin(); cit != _row_v.end(); cit++)
		{
			cout << "(" << (*cit).first << "/" << (*cit).second << ")\t";
		}
		cout << endl;
	}

	// print result
	cout << endl << "Number " << this->ori_lo << "*" << this->ori_ro << " = ";
	cout << rv_str << endl << endl;
}


/////////////////////////////////////////////////////////////
// Helper functions

/**
 * Check sign of the operands and remove the sign from the operands
 * We would store the sign in this->op_sign applying it to the result finally
 * This would be called after ensure_string(left, right)
 * @method check_sign
 * @param left T, right T
 * @return void
 */
template <typename TL, typename TR>
void LatticeMultiplication<TL, TR>::check_sign(TL left, TR right)
{
	if(this->lo.empty() || this->ro.empty() )
		return;

	if(this->lo[0] == '-')
	{
		this->op_sign *= -1;
		this->lo = this->lo.substr(1);
	}

	if(this->ro[0] == '-')
	{
		this->op_sign *= -1;
		this->ro = this->ro.substr(1);
	}

	// Store the size of left and right operands
	this->lo_size = (int)this->lo.size();
	this->ro_size = (int)this->ro.size();
}

/**
 * Make sure all two inputs be converted to string
 * Example: 10.23 would be 1023 and store 2 as length of decimal
 * @method ensure_string
 * @param left T, right T
 * @return void
 */
template <typename TL, typename TR>
void LatticeMultiplication<TL, TR>::ensure_string(TL left, TR right)
{
	// Cope with left operand
	this->lo = this->to_string<TL>(left);

	// Cope with right operand
	this->ro = this->to_string<TR>(right);
}

/**
 * Convert int, float or double to string by removing .
 * Example: 10.23 would be 1023 and store 2 as length of decimal
 * @method to_string
 * @param _v T
 * @return string
 */
template <typename TL, typename TR> 
template <typename T>
 string LatticeMultiplication<TL, TR>::to_string(T _v)
 {
 	string _rv;
 	ostringstream ss;
	string _d;
	unsigned int _pos = string::npos;
	unsigned int _l_demical = 0;
	string _s_radix;
	string _s_decimal;

	ss << _v;
	// Trim all postfix zeros
	_d = this->rtrim(ss.str(), "0");

	// Find . in the string
	_pos = _d.find(".");
	if(_pos == string::npos)
	{
		_rv = _d;
	}
	else
	{
		// Split float point value into two parts with .
		_s_radix = _d.substr(0, _pos);
		_s_decimal = _d.substr(_pos+1);
		
		_rv = _s_radix;
		if(_s_decimal.size() > 0)
		{
			_rv += _s_decimal;
			this->length_decimal += (int)_s_decimal.size();
		}
	}

	return _rv;
 }

/**
 * Convert an Interger to an intergar array with all its digits
 * @method itov
 * @param int n
 * @return vector<int>
 */
template <typename TL, typename TR> 
vector<int> LatticeMultiplication<TL, TR>::itov(int n)
{
	vector<int> r;
	int _t = n;
	while(_t/10 > 0)
	{
		r.insert(r.begin(), _t%10);
		_t /= 10;
	}
	if(_t > 0 )
		r.insert(r.begin(), _t); // Append the last one
	return r;
}

/**
 * Trim white spaces or specified characters
 * @method ltrim
 * @param _s const string&, delimters const string&
 * @return string
 */
template <typename TL, typename TR> 
string 	LatticeMultiplication<TL, TR>::ltrim(const string &_s, const string &delimiters/* = " \t\r\n\0\a\b\f\v"*/)
{
	size_t at = _s.find_first_not_of(delimiters);
    return at == string::npos ? _s : _s.substr(at);
}

/**
 * Trim white spaces or specified characters
 * @method rtrim
 * @param _s const string&, delimters const string&
 * @return string
 */
template <typename TL, typename TR> 
string 	LatticeMultiplication<TL, TR>::rtrim(const string &_s, const string &delimiters/* = " \t\r\n\0\a\b\f\v"*/)
{
	size_t at = _s.find_last_not_of(delimiters);
    return at == string::npos ? _s : _s.substr(0, at+1);
}

/**
 * Trim white spaces or specified characters
 * @method trim
 * @param _s const string&, delimters const string&
 * @return string
 */
template <typename TL, typename TR> 
string 	LatticeMultiplication<TL, TR>::trim(const string &_s, const string &delimiters/* = " \t\r\n\0\a\b\f\v"*/)
{
    string str = _s;
    size_t at_last = str.find_last_not_of(delimiters);
    size_t at_first = str.find_first_not_of(delimiters);
    if (at_last != string::npos) str.erase(at_last+1);
    if (at_first != string::npos) str.erase(0,at_first);
    return str;
}

#endif