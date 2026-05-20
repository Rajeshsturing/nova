#macro DECLARE_CRITICAL_SECTION(_name_) \
dim g_nCS##_name_ \
g_nCS##_name_ = CLng(0)

#macro TRY_ENTER_CRITICAL_SECTION(_name_) \
if (g_nCS##_name_ = 0) then \
g_nCS##_name_ = CLng(1)

#macro END_TRY_CRITICAL_SECTION(_name_) \
g_nCS##_name_ = CLng(0) \
end if
