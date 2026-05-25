using nxm.setup.uss;
using nxm.setup.uss.data;
using nxm.system;
using nxm.system.execution;
using nxm.system.execution.context;
using nxm.system.io;
using nxm.system.logging;
using nxm.system.logging.storage;

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace nxhub
{
    public class navo_use
    {
        static navo_use()
        {
            uss_hub.TheInstance.register_uss_provider(navo_engine_uss);
        }

        public static _result_<(_result_ start_result_, bool exit_now_)> do_engine_update()
        {
            _result_<updatable_target_info> resCheck = check_for_updates();
            if (!resCheck)
            {
                return _result_<(_result_, bool)>.CAST_ERROR(resCheck);
            }
            else
            {
                if (resCheck.result_ != null)
                {
                    _result_<(_result_ start_result_, bool exit_now_)> resStart = _start_update(resCheck.result_);

                    return resStart;
                }
                else
                {
                    return _result_.OK((_result_.OK(), false));
                }
            }
        }

        private static iupdate_service_subscriber navo_engine_uss()
        {
            just_copy_files_uss oUSS = new just_copy_files_uss(
                "navo.client.engine",
                "navo.client.engine",
                () => new (string, string)[] { ("main", Path.GetDirectoryName(Environment.GetCommandLineArgs()[0])) },
                () => new string[] {"navo2*" },
                () => new string[] { "nxm.*" });

            return oUSS;
        }

        /// <summary>call update info service for list of available new packages</summary>
        public static _result_<updatable_target_info> check_for_updates()
        {
            return _update_wrapper(
                call_context_ =>
                {
                    call_context_.log.info_text("checking for new updates");
                    (_result_ result_, IEnumerable<updatable_target_info> data_) resGet = uss_hub.TheInstance.get_updatable_targets(call_context_).Result;

                    if (resGet.result_)
                    {
                        IEnumerable<updatable_target_info> collAvailablePackages = resGet.data_;

                        updatable_target_info oUTI = collAvailablePackages.FirstOrDefault();

                        if (oUTI == null)
                        {
                            call_context_.log.info_text("check successed but nothing new has been found");
                        }
                        else
                        {
                            call_context_.log.info_text($"check successed. new package [{oUTI.package_info.channel}/{oUTI.package_info.version}] has been found");
                        }

                        return oUTI;
                    }
                    else
                    {
                        call_context_.log.store(resGet.result_);
                        return null;
                    }
                });
        }

        private static _result_<(_result_ start_result_, bool exit_now_)> _start_update(updatable_target_info oUTI)
        {
            return _update_wrapper(
                call_context_ =>
                {
                    (_result_ start_result_, bool exit_now_) oPair = uss_hub.TheInstance.start_update(call_context_, oUTI).Result;

                    return oPair;
                });
        }

        private static _result_<TResult> _update_wrapper<TResult>(Func<icall_context, TResult> fpBody)
        {
            return safe_call.try_catch_result(
                () =>
                {
                    using (ilog_storage oLogStorage = text_stream_log_storage.fixed_log(null,
                        Path.Combine(file_system_path_provider_.system.setup_root, "logs", "navo.client.engine.setup.txt")))
                    {
                        using (ilog oLog = log.create_with_storage_as_source(oLogStorage, "navo-use"))
                        {
                            using (call_context oCallContext = new call_context("root", oLog: oLog))
                            {
                                return fpBody(oCallContext);
                            }
                        }
                    }
                });
        }
    }
}
