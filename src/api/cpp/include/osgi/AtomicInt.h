/*=============================================================================

  Copyright (c) Sascha Zelzer

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/


#ifndef OSGI_ATOMICINT_H_
#define OSGI_ATOMICINT_H_

#include <osgi/Config.h>
#include <osgi/Threads.h>

namespace osgi {

/**
 * \cond internal
 *
 * This class acts as an atomic integer.
 *
 * The integer value represented by this class can be incremented
 * and decremented atomically. This is often useful in reference
 * counting scenarios to minimize locking overhead in multi-threaded
 * environments.
 */
class AtomicInt : private OSGI_DEFAULT_THREADING<AtomicInt>
{

public:

  AtomicInt(int value = 0) : m_ReferenceCount(value) {}

  /**
   * Increase the reference count atomically by 1.
   *
   * \return <code>true</code> if the new value is unequal to zero, <code>false</code>
   *         otherwise.
   */
  inline bool ref() const
  { return AtomicIncrement(m_ReferenceCount) != 0; }

  /**
   * Decrease the reference count atomically by 1.
   *
   * \return <code>true</code> if the new value is unequal to zero, <code>false</code>
   *         otherwise.
   */
  inline bool deref() const
  { return AtomicDecrement(m_ReferenceCount) != 0; }

  /**
   * Returns the current value.
   *
   */
  inline operator int() const
  {
    IntType curr(0);
    AtomicAssign(curr, m_ReferenceCount);
    return curr;
  }

private:

  mutable IntType m_ReferenceCount;

};

/** \endcond */

} // end namespace osgi

#endif // OSGI_ATOMICINT_H_
