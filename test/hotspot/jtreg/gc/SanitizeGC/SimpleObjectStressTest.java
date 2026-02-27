/*
 * Copyright (c) 2025, IBM.
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

/*
 * @test SimpleObjectStressTest.java
 * @summary Simple object GC stress test.
 * @build gc.SanitizeGC.SanitizeGCTestObj
 * @run main/othervm/timeout=300 -XX:-UseCompressedOops -XX:+UseG1GC -XX:+SanitizeGC -Xmx200m -Xlog:gc+remset=trace,gc+refine=trace,gc+barrier=trace,gc+phases=trace,gc+task=debug,gc+verify=debug,gc+region=trace gc.SanitizeGC.SimpleObjectStressTest
 */

package gc.SanitizeGC;

import java.util.ArrayList;
import java.util.List;
import java.lang.ref.WeakReference;
import gc.SanitizeGC.SanitizeGCTestObj;

public class SimpleObjectStressTest {
    public static void main(String[] args) {
        System.out.println("Starting simple object stress test.");

        try {
            for (int i = 0; i < 25_000; i++) {
                // allocate a lot of short-lived objects
                List<SanitizeGCTestObj> list = new ArrayList<>();
                for(int j = 0; j < 2000; j++) {
                    SanitizeGCTestObj obj;
                    if (j % 2 == 0) {
                        obj = new SanitizeGCTestObj(1138);
                    } else if (j % 3 == 0) {
                        obj = new SanitizeGCTestObj(10_381);
                    } else {
                        obj = new SanitizeGCTestObj(394);
                    }

                    list.add(obj);
                }

                if (i % 10 == 0) {
                    System.out.println("Iteration: " + i);
                }

                if (i != 0 && i % 5000 == 0) {
                    System.out.println("Triggering full GC.");
                    // Uses a hack to trigger a full gc here from:
                    // https://stackoverflow.com/a/6915221
                    Object obj = new Object();
                    WeakReference ref = new WeakReference<Object>(obj);
                    obj = null;
                    while(ref.get() != null) {
                        System.gc();
                    }
                }
            }
        } catch (OutOfMemoryError e) {
            System.out.println("Out of memory.");
        }
    }
}
