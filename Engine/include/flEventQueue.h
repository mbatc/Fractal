#pragma once

#include "flEvent.h"
#include "flThreadQueue.h"

namespace Fractal
{
  class Impl_EventQueue;

  /**
   * @brief An event queue for system receiving events.
   *
   * An EventQueue can be used to receive events from the operating
   * system. OS events will be forwarded individually to every EventQueue instance.
   *
   * Custom events can also be posted via the Event classes custom event
   * mechanism.
   */
  class flEXPORT EventQueue : public Interface
  {
    flPIMPL_DEF(EventQueue);

  public:
    /**
     * @brief Set a filter for this event queue.
     *
     * This will only allow events of the specified type to be added to this
     * event queue. Event types can be combined to allow more than 1 or more
     * types.
     *
     * @param [in] type Any combination of the EventType bit field.
     */
    void SetFilter(flIN EventType type);

    /**
     * @brief Set a filter callback for this event queue.
     *
     * This can be used to implement more complex filters based on more than
     * just the type of event. The callback should return true to allow the
     * event to be added, and false to reject it.
     *
     * If a EventType filter has been set, both the callback test and type test must
     * pass for the Event to be accepted.
     *
     * @param [in] FilterFunc A pointer to the callback that should be used to filter Events.
     * @param [in] pUserData  A void * that is forwarded to the FilterFunc. This can be used to
     *                   pass custom data to the callback.
     */
    void SetFilter(flIN bool (*FilterFunc)(Event*, void*), void* pUserData = nullptr);

    /**
     * @brief Get the next event without removing it from the queue.
     *
     * @param [out] pEvent A pointer to an event struct to copy the next event to.
     *
     * @return Returns true if the next event exists, otherwise false is returned.
     */
    bool PeekEvent(flOUT Event* pEvent) const;

    void SetEventCallback(flIN void(*EventHandler)(Event*, void*), void* pUserData = nullptr);

    /**
     * @brief Get the next event and remove it from the queue.
     *
     * @param [out] pEvent A pointer to an event struct to copy the next event to.
     *
     * @return Returns true if the next event exists, otherwise false is returned.
     */
    bool NextEvent(flOUT Event* pEvent);

    /**
     * @brief Add an event to this event queue instance.
     *
     * This function will add an event to this event queue. If the event filter has been set
     * and the passed event is not included in that filter, this function will fail.
     *
     * @param [in] pEvent The event to add to the queue. This event should not be destroyed,
     *                    as the event queue will handle destroying the event data.
     *
     * @return Returns true if the event was successfully added. If the function fails for any
     *         reason, false is returned.
     */
    bool PostEvent(flIN Event* pEvent);

    /**
     * @brief Get the number of events currently in the queue.
     *
     * @return The number of events in the queue.
     */
    int64_t GetEventCount() const;

    /**
     * @brief Clear the event queue.
     *
     * Clears all events from the event queue. This may stop them from being processed.
     */
    void Clear();

    /**
     * @brief Add an event to all event queues.
     *
     * This function can be used to post an event to all existing event queues. Any event
     * queue that has the correct filter set will receive the event.
     *
     * @param [in] pEvent The event to add to the queue.
     *
     * @return Returns true if the event was added to any of the existing EventQueue's.
     *         If no event queue accepted the event, false is returned.
     */
    static bool flCCONV PostGlobalEvent(flIN Event* pEvent);

    /**
     * @brief Get the system event thread.
     *
     * @return The ThreadQueue used to process system events.
     */
    static ThreadQueue* flCCONV GetEventThread();
  };
}
