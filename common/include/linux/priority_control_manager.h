/*
 *
 * (C) COPYRIGHT ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you can access it online at
 * http://www.gnu.org/licenses/gpl-2.0.html.
 *
 * SPDX-License-Identifier: GPL-2.0
 *
 *//* SPDX-License-Identifier: GPL-2.0 */
/*
 *
 * (C) COPYRIGHT 2020 ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you can access it online at
 * http://www.gnu.org/licenses/gpl-2.0.html.
 *
 */

#ifndef _PRIORITY_CONTROL_MANAGER_H_
#define _PRIORITY_CONTROL_MANAGER_H_

#include <linux/mm.h>
#include <linux/of.h>
#include <linux/version.h>

struct priority_control_manager_device;

/**
 * struct priority_control_manager_ops - Callbacks for priority control manager operations
 *
 * @pcm_scheduler_priority_check: Callback to check if scheduling priority level can be requested
 */
struct priority_control_manager_ops {
	/**
	 * pcm_scheduler_priority_check: This function can be used to check what priority its work
	 *                               would be treated as based on the requested_priority value.
	 *
	 * @pcm_dev:                     The priority control manager through which the request is
	 *                               being made.
	 * @task:                        The task struct of the process requesting the priority check.
	 * @requested_priority:          The priority level being requested.
	 *
	 * The returned value will be:
	 *   The same as requested_priority if the process has permission to use requested_priority
	 *   A lower priority value if the process does not have permission to use requested_priority
	 *
	 * requested_priority has the following value range:
	 *   0-3 : Priority level, 0 being highest and 3 being lowest
	 *
	 * Return: The priority that would actually be given, could be lower than requested_priority
	 */
	int (*pcm_scheduler_priority_check)(
		struct priority_control_manager_device *pcm_dev,
		struct task_struct *task, int requested_priority);
};

/**
 * struct priority_control_manager_device - Device structure for a priority
 *                                          control manager
 *
 * @ops  - Callbacks associated with this device
 * @data - Pointer to device private data
 *
 * In order for a systems integrator to implement custom restrictions on which
 * processes can use certain GPU scheduling priorities, they must provide a
 * platform-specific driver module which implements this interface.
 *
 * This structure should be registered with the platform device using
 * platform_set_drvdata().
 */
struct priority_control_manager_device {
	struct priority_control_manager_ops ops;
	void *data;
};

#endif /* _PRIORITY_CONTROL_MANAGER_H_ */
