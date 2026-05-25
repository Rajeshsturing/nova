using System.Collections.Generic;
using System.IO;

namespace navo2012.remote_posnet
{
    public class file_util
    {
        /// <summary>
        /// searches for files matching specified mask</summary>
        public static IEnumerable<string> _naked_find_file_names(string strDirectoryPath, string strMask, bool bRecursive)
        {
            return _naked_find_item_names(strDirectoryPath, strMask, bRecursive, true, false);
        }
        /// <summary>
        /// looks for files or directories in specified dir matching mask
        /// search can be recursive and filter only files, dirs, or both</summary>
        public static IEnumerable<string> _naked_find_item_names(string strDirectoryPath, string strMask,
               bool bRecursive, bool bSearchFiles, bool bSearchDirs)
        {
            //detect void call ? 

            if (bSearchDirs)
            {
                string[] strDirNames = Directory.GetDirectories(strDirectoryPath, strMask,
                   bRecursive ? SearchOption.AllDirectories : SearchOption.TopDirectoryOnly);

                foreach (string strDirName in strDirNames)
                {
                    yield return strDirName;
                }
            }

            if (bSearchFiles)
            {
                string[] strFileNames = Directory.GetFiles(strDirectoryPath, strMask,
                    bRecursive ? SearchOption.AllDirectories : SearchOption.TopDirectoryOnly);

                foreach (string strFileName in strFileNames)
                {
                    yield return strFileName;
                }
            }
        }
    }
}