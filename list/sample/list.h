/******************************************************************************
**                                                                           **
**    Sample code for the stack data structure                               **
**                                                                           **
**    This program is free software: you can redistribute it and/or modify   **
**    it under the terms of the GNU General Public License as published by   **
**    the Free Software Foundation, either version 3 of the License, or      **
**    (at your option) any later version.                                    **
**                                                                           **
**    This program is distributed in the hope that it will be useful,        **
**    but WITHOUT ANY WARRANTY; without even the implied warranty of         **
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          **
**    GNU General Public License for more details.                           **
**                                                                           **
**    You should have received a copy of the GNU General Public License      **
**    along with this program.  If not, see <http://www.gnu.org/licenses/>.  **
**                                                                           **
******************************************************************************/

#ifndef LIST_H_
# define LIST_H_

# include "../list.hxx"

/// @brief This macro call will be replace at compile-time by
//  prototypes and struct declarations for the list data-structure
LIST_HEADER(int, list)

#endif /* !LIST_H_ */
